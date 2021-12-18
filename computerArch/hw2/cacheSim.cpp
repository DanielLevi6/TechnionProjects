/* 046267 Computer Architecture - Winter 20/21 - HW #2 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using std::FILE;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::stringstream;


class Way{
public:
	unsigned address;
    unsigned tag;
    unsigned valid_bit;
    unsigned dirty_bit;
    unsigned LRU;



    Way() : tag(0) , valid_bit(0) , dirty_bit(0) , LRU(0) {}
    Way(unsigned address , unsigned tag) : address(address) , tag(tag) , valid_bit(1) , dirty_bit(0) , LRU(0) {}
    ~Way() = default;

};

class Line{

    Way* ways;
    unsigned LRU;
    unsigned k_ways;

public:

    Line() : LRU(0) {}
    ~Line() {
        if(ways != NULL) {
            delete[] ways;
        }
    }

    void Init(unsigned k_ways) {
        this->k_ways = k_ways;
        ways = new Way[k_ways]();
    }

    Way* search(unsigned tag) {
        for(unsigned i=0; i<k_ways; i++) {
            if(ways[i].tag==tag && ways[i].valid_bit) {
                return ways+i;
            }
        }
        return NULL;
    }
	
	bool change_valid_bit(Way* found){
		for(unsigned i=0; i<k_ways; i++){
			if(ways[i].tag==found->tag){
				ways[i].valid_bit = 0;
				return true;
			}
		}
		return false;
	}

    Way* update(Way& found , int dirty, int snoop) {
		Way* ret = NULL;
        /*We try to find an empty way*/
        for(unsigned i=0; i<k_ways; i++) {
            if(ways[i].valid_bit==0) {
                ways[i].tag = found.tag;
				ways[i].address = found.address;
                ways[i].LRU = 0;
				if(dirty) ways[i].dirty_bit = 1;
                for(unsigned j=0; j<k_ways; j++) {
                    if(ways[j].valid_bit){
                        ++ways[j].LRU;
                    }
                }
                ways[i].valid_bit = 1;
                return ret;
            }
        }

        /*We didn't find an empty way*/



        for(unsigned j=0; j<k_ways; j++) {
            if(ways[j].LRU==k_ways-1) {
                /*update*/
				if(ways[j].dirty_bit || snoop){
					
					ret = new Way(ways[j].address , ways[j].tag);
					
				}
                ways[j].tag= found.tag;
				ways[j].address = found.address;
				if(dirty) ways[j].dirty_bit = 1;
                else ways[j].dirty_bit = 0;
                ways[j].LRU = 0;
        
            } else {
                ++ways[j].LRU;
            }
        }
        
        return ret;
    }
	void update_dirty_bit(Way* found, int value){
		for(unsigned i=0; i<k_ways; i++) {
		if(ways[i].tag==found->tag && ways[i].valid_bit){
		ways[i].dirty_bit = value;
		}
		}
		return;
	}
	
	bool update_LRU(Way* found, unsigned dirty_bit){
		unsigned origin_LRU = 0;
		unsigned foundinl2;
		bool ret_dirty = false;
		for(unsigned i=0; i<k_ways; i++) {
            if(ways[i].tag==found->tag && ways[i].valid_bit) {
				origin_LRU = ways[i].LRU;
				foundinl2=1;
                ways[i].LRU = 0;
				if(ways[i].dirty_bit)ret_dirty = true;
				if(dirty_bit==1) ways[i].dirty_bit = 1;
				
            }
      	}
		/*update others LRU */
		if(foundinl2){
		for(unsigned i=0; i<k_ways; i++) {
            if((ways[i].tag != found->tag) && ways[i].valid_bit && (ways[i].LRU < origin_LRU))
				ways[i].LRU++;
      	}
		}
		 return ret_dirty;
	}
	
	
};


class L1{

    Line* table;
    unsigned blocks_num;
    unsigned number_of_lines;

public:

    L1() {}
    L1(unsigned L1_size, unsigned Bsize, unsigned L1Assoc) : blocks_num((unsigned)pow(2,L1_size-Bsize)) {
        number_of_lines=blocks_num/L1Assoc;
        table = new Line[number_of_lines]();
        for(unsigned i=0; i<(number_of_lines); i++) {
            table[i].Init(L1Assoc);
        }
    }
    ~L1() {
        delete[] table;
    }

    Way* search(unsigned address, unsigned Bsize) {
        unsigned set = address >> Bsize;
        set = set % number_of_lines;

        Way* found=table[set].search(address >> ( Bsize+(unsigned)log2(number_of_lines)));


        return found;
    }


    Line& operator[](unsigned i) { return table[i]; }

};

class L2{

    Line* table;
    unsigned blocks_num;
    unsigned number_of_lines;

public:

    L2() {}
    L2(unsigned L2_size, unsigned Bsize, unsigned L2Assoc) : blocks_num((unsigned)pow(2,L2_size-Bsize)) {
        number_of_lines=blocks_num/L2Assoc;
        table = new Line[number_of_lines]();
        for(unsigned i=0; i<(number_of_lines); i++) {
            table[i].Init(L2Assoc);
        }
    }
    ~L2() {
        delete[] table;
    }

    Way* search(unsigned address, unsigned Bsize) {
        unsigned set = address >> Bsize;
        set = set % number_of_lines;

        Way* found=table[set].search(address >> ( Bsize+(unsigned)log2(number_of_lines)));
        
        return found;
    }

    Line& operator[](unsigned i) { return table[i]; }
    
};

class Cache{

    unsigned MemCyc;
    unsigned BSize;
    unsigned L1Size;
    unsigned L2Size;
    unsigned L1Assoc;
    unsigned L2Assoc;
    unsigned L1Cyc;
    unsigned L2Cyc;
    unsigned WrAlloc;

    double L1MissCounter;
    double L1Counter;
    double L2MissCounter;
    double L2Counter;

    double total_time;

    L1 L1_table;
    L2 L2_table;

public:

    Cache() {}
    Cache(unsigned MemCyc, unsigned BSize, unsigned L1Size, unsigned L2Size, unsigned L1Assoc,
             unsigned L2Assoc, unsigned L1Cyc, unsigned L2Cyc, unsigned WrAlloc) : MemCyc(MemCyc) , 
             BSize(BSize) , L1Size(L1Size) , L2Size(L2Size) , L1Assoc((L1Assoc==0)? 1 : pow(2,L1Assoc)) , L2Assoc((L2Assoc==0)? 1 : pow(2,L2Assoc)) ,
             L1Cyc(L1Cyc) , L2Cyc(L2Cyc) , WrAlloc(WrAlloc) , L1MissCounter(0) , L1Counter(0) ,
             L2MissCounter(0) , L2Counter(0) , total_time(0) , L1_table(L1Size,BSize,this->L1Assoc) , 
             L2_table(L2Size,BSize,this->L2Assoc) { }
    
    ~Cache() = default;

    void read(unsigned address) {
		Way* snoop = NULL;
		Way* dirty = NULL;
        Way* foundL1 = L1_table.search(address,BSize);
        L1Counter++;
        total_time+=L1Cyc;

        Way* foundL2=NULL;

        if(foundL1 == NULL) {
            /* Didn't found in L1*/
            L2Counter++;
            L1MissCounter++;
            total_time+=L2Cyc;

            foundL2 = L2_table.search(address,BSize);
            if(foundL2 != NULL) {
				bool update_L1_dirty = false;
                /*found in L2, calculate the hit time*/
				/*update LRU in L2*/
                unsigned setL2 = address >> this->BSize;
                setL2 = setL2 % (((unsigned)pow(2,L2Size-BSize))/L2Assoc);
				
				/* update_LRU return true if the way is dirty*/
				if(L2_table[setL2].update_LRU(foundL2,0)){
					/* we will update L1 as dirty*/ 
					//update_L1_dirty = true;
					
					/* only one level can be dirty so we clean L2*/
					//L2_table[setL2].update_valid_bit(foundL2,0);
				}
				
				/*update L1*/
				unsigned setL1 = address >> this->BSize;
                setL1 = setL1 % (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
				
				/* dirty is pointer to way if we removed way that was dirty */
                dirty = L1_table[setL1].update(*foundL2,(int)update_L1_dirty,0);
				if(dirty){
					
					/*need to update value in L2 hence we update LRU*/
					unsigned dirty_set = dirty -> address;
					dirty_set = dirty_set >> this->BSize;
					dirty_set = dirty_set % (((unsigned)pow(2,L2Size-BSize))/L2Assoc);
					
					/* we update L2 and make it dirty*/
					L2_table[dirty_set].update_LRU(dirty,1);
					//delete dirty;
				}
				
                return;
            } else {
                /*Didn't find in L1 and L2
                Update the cache*/
                L2MissCounter++;
                total_time+=MemCyc;
                
                unsigned set_L1=address >> this->BSize;
                set_L1 = set_L1 % (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
                unsigned set_L2=address >> this->BSize;
                set_L2 = set_L2 % (((unsigned)pow(2,L2Size-BSize))/L2Assoc);

				unsigned tag1 = ( BSize+(unsigned)log2(pow(2,L1Size-BSize)/L1Assoc));
				unsigned tag2 = ( BSize+(unsigned)log2(pow(2,L2Size-BSize)/L2Assoc));
				
                Way new_way_L1(address , address >> tag1);/////////
                Way new_way_L2(address , address >> tag2);/////////
				
				/*L2 return the way that it removed. we need to check if we have it in L1 because of inclusion */
				snoop = L2_table[set_L2].update(new_way_L2,0,1);
					if(snoop){
						Way *snoopL1 = L1_table.search(snoop->address,BSize);
						if(snoopL1){
							/*need to delete in L1 - inclusion */
						unsigned set_L1_snoop = snoopL1 -> address;
						set_L1_snoop = set_L1_snoop >> this->BSize;
						set_L1_snoop = set_L1_snoop % (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
						if(!L1_table[set_L1_snoop].change_valid_bit(snoopL1)){
							printf("error");
						}						
						}
					}
				/*we insert new way to L1 and it is clean because it is a read function */
                dirty = L1_table[set_L1].update(new_way_L1,0,0);
				
				if(dirty){
					/*need to update value in L2 hence we update LRU*/
					
					set_L2 = dirty -> address;
					set_L2 = set_L2 >> this->BSize;
					set_L2 = set_L2 % (((unsigned)pow(2,L2Size-BSize))/L2Assoc);
					/* we update L2 and make it dirty*/
					L2_table[set_L2].update_LRU(dirty,1);
                }
            }
        } else {
			 /** found in L1 */
			 /*need to update LRU*/
            /* Calculate the hit time*/
			unsigned set_L1 = foundL1 -> address;
			set_L1 = set_L1 >> this->BSize;
			set_L1 = set_L1 % (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
			/*we update L1 LRU and no dirty because we only read */
			L1_table[set_L1].update_LRU(foundL1,0);
           
            

            return;
        }

    }

    void write(unsigned address) {
		Way* snoop = NULL;
		Way* dirty = NULL;
        Way* foundL1 = L1_table.search(address,BSize);
        L1Counter++;
        total_time+=L1Cyc;

        Way* foundL2=NULL;

        if(foundL1 == NULL) {
            /* Didn't found in L1*/
            L2Counter++;
            L1MissCounter++;
            total_time+=L2Cyc;

            foundL2 = L2_table.search(address,BSize);
            if(foundL2 != NULL) {
                /*found in L2, calculate the hit time*/
				
				unsigned setL1 = address >> this->BSize;
				//unsigned debug1 = (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
                setL1 = setL1 % (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
				
				unsigned setL2 = address >> this->BSize;
				//unsigned debug2 = (((unsigned)pow(2,L2Size-BSize))/L2Assoc);
                setL2 = setL2 % (((unsigned)pow(2,L2Size-BSize))/L2Assoc);
				
                if(this->WrAlloc) {
					
					/* update L2 LRU and make it clean because we insert to L1 and it will be dirty there */
					L2_table[setL2].update_LRU(foundL2,0);
					//L2_table[setL2].update_dirty_bit(foundL2,0);
                    
					/* insert to L1 and make it dirty */
					dirty = L1_table[setL1].update(*foundL2,1,0);
					if(dirty){
						/*need to update value in L2 hence we update LRU*/
						unsigned set_L2_dirty = dirty -> address;
						set_L2_dirty = set_L2_dirty >> this->BSize;
						set_L2_dirty = set_L2_dirty % (((unsigned)pow(2,L2Size-BSize))/L2Assoc);
						/* we update L2 and make it dirty*/
						L2_table[set_L2_dirty].update_LRU(dirty,1);
					}
					

                } else {
					
                    /*Calculate hit time*/
					/* update LRU and make it dirty because we write*/ 
					L2_table[setL2].update_LRU(foundL2,1);

                }
                
                return;
            } else {
                
                //wasn't found
                L2MissCounter++;
                total_time+=MemCyc;

                if(this->WrAlloc) {

                    unsigned set_L1=address >> this->BSize;
					//unsigned debug = (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
                    set_L1 = set_L1 % (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
					
					//unsigned debug2 = (((unsigned)pow(2,L2Size-BSize))/L2Assoc);
                    unsigned set_L2=address >> this->BSize;
                    set_L2 = set_L2 % (((unsigned)pow(2,L2Size-BSize))/L2Assoc);

					unsigned tag1 = ( BSize+(unsigned)log2(pow(2,L1Size-BSize)/L1Assoc));
					unsigned tag2 = ( BSize+(unsigned)log2(pow(2,L2Size-BSize)/L2Assoc));
					
					Way new_way_L1(address , address >> tag1);
					Way new_way_L2(address , address >> tag2);
					/*insert to L2 and make it clean because we insert as dirty in L1 */
					snoop = L2_table[set_L2].update(new_way_L2,0,1);
					/*we check if we removed way that is found in L1 */
					if(snoop){
						Way *snoopL1 = L1_table.search(snoop->address,BSize);
						if(snoopL1){
							/*need to delete in L1 - inclusion*/
							
						unsigned set_L1_snoop = snoopL1 -> address;
						set_L1_snoop = set_L1_snoop >> this->BSize;
						set_L1_snoop = set_L1_snoop % (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
						if(!L1_table[set_L1_snoop].change_valid_bit(snoopL1)){
							printf("error");
						}						
						}
					}
					
                    dirty = L1_table[set_L1].update(new_way_L1,1,0);
                    
					
					if(dirty){
						/*need to update value in L2 hence we update LRU*/
						set_L2 = dirty -> address;
						set_L2 = set_L2 >> this->BSize;
						set_L2 = set_L2 % (((unsigned)pow(2,L2Size-BSize))/L2Assoc);
						L2_table[set_L2].update_LRU(dirty,1);
					}
					
					
					

                } else {
                    //Calculate the hit time
                }
            }
        } else {
            /** found in L1 */
            /* Calculate the hit time*/
			/*need to update LRU and add dirty bit*/

			unsigned set_L1 = foundL1 -> address;
			set_L1 = set_L1 >> this->BSize;
			set_L1 = set_L1 % (((unsigned)pow(2,L1Size-BSize))/L1Assoc);
			L1_table[set_L1].update_LRU(foundL1,1);

            return;
        }


    }


    double getL1MissRate() {
        return L1MissCounter/L1Counter;
    }

    double getL2MissRate() {
        return L2MissCounter/L2Counter;
    }

    double getAvgAccTime() {
        return total_time/L1Counter;
    }


};



int main(int argc, char **argv) {

	if (argc < 19) {
		cerr << "Not enough arguments" << endl;
		return 0;
	}

	// Get input arguments

	// File
	// Assuming it is the first argument
	char* fileString = argv[1];
	ifstream file(fileString); //input file stream
	string line;
	if (!file || !file.good()) {
		// File doesn't exist or some other error
		cerr << "File not found" << endl;
		return 0;
	}

	unsigned MemCyc = 0, BSize = 0, L1Size = 0, L2Size = 0, L1Assoc = 0,
			L2Assoc = 0, L1Cyc = 0, L2Cyc = 0, WrAlloc = 0;

	for (int i = 2; i < 19; i += 2) {
		string s(argv[i]);
		if (s == "--mem-cyc") {
			MemCyc = atoi(argv[i + 1]);
		} else if (s == "--bsize") {
			BSize = atoi(argv[i + 1]);
		} else if (s == "--l1-size") {
			L1Size = atoi(argv[i + 1]);
		} else if (s == "--l2-size") {
			L2Size = atoi(argv[i + 1]);
		} else if (s == "--l1-cyc") {
			L1Cyc = atoi(argv[i + 1]);
		} else if (s == "--l2-cyc") {
			L2Cyc = atoi(argv[i + 1]);
		} else if (s == "--l1-assoc") {
			L1Assoc = atoi(argv[i + 1]);
		} else if (s == "--l2-assoc") {
			L2Assoc = atoi(argv[i + 1]);
		} else if (s == "--wr-alloc") {
			WrAlloc = atoi(argv[i + 1]);
		} else {
			cerr << "Error in arguments" << endl;
			return 0;
		}
	}

    Cache cache(MemCyc,BSize,L1Size,L2Size,L1Assoc,L2Assoc,L1Cyc,L2Cyc,WrAlloc);

	while (getline(file, line)) {

		stringstream ss(line);
		string address;
		char operation = 0; // read (R) or write (W)
		if (!(ss >> operation >> address)) {
			// Operation appears in an Invalid format
			cout << "Command Format error" << endl;
			return 0;
		}

		// DEBUG - remove this line
		//cout << "operation: " << operation;

		string cutAddress = address.substr(2); // Removing the "0x" part of the address

		// DEBUG - remove this line
		//cout << ", address (hex)" << cutAddress;

		unsigned long int num = 0;
		num = strtoul(cutAddress.c_str(), NULL, 16);

		// DEBUG - remove this line
		//cout << " (dec) " << num << endl;


        if(operation=='w') {
            cache.write(num);
        } else if(operation=='r') {
            cache.read(num);
        }

	}

	double L1MissRate;
	double L2MissRate;
	double avgAccTime;

    L1MissRate=cache.getL1MissRate();
    L2MissRate=cache.getL2MissRate();
    avgAccTime=cache.getAvgAccTime();

	printf("L1miss=%.03f ", L1MissRate);
	printf("L2miss=%.03f ", L2MissRate);
	printf("AccTimeAvg=%.03f\n", avgAccTime);

	return 0;
}