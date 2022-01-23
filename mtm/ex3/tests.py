from hw3_part1 import find_k_most_expensive_products, find_best_selling_product
from hw3_part2 import check_match, get_palindrom_dict

def compare_dict1_to_dict2 (dict1, dict2):
    for key in dict1:
        assert key in dict2
        assert set(dict1[key]) == set(dict2[key]) 

def compare_dictionaries (dict1, dict2):
    compare_dict1_to_dict2(dict1, dict2)
    compare_dict1_to_dict2(dict2, dict1)

def compare_best_selling_product (function_res, best_selling_product):
    assert function_res[0] == best_selling_product[0]
    assert abs(function_res[1] - best_selling_product[1]) <= 10 ** (-3)
    

#### Tests for first part ####
curr_file = 'example.txt'
most_expensive_products = [[], ['apple'], ['apple', 'banana'], ['apple', 'banana', 'orage'], ['apple', 'banana', 'orage', 'pear']]
for i, most_expensive_product in enumerate(most_expensive_products):
    assert (find_k_most_expensive_products(curr_file, i) == most_expensive_product)

compare_best_selling_product(find_best_selling_product('example.txt'), ('banana', 126.2625))

most_expensive_products = [[], ['carrot'], ['carrot', 'apple', 'banana', 'orage', 'pear']]
for most_expensive_product in most_expensive_products:
    assert (find_k_most_expensive_products('example1.txt', len(most_expensive_product)) == most_expensive_product)

compare_best_selling_product(find_best_selling_product('example1.txt'), ('carrot', 18.0))

#### Tests for second part ####
palindrom_dict = {1: ['A', 'b', 'b', 'A', 'c', 'a', 'B', 'B', 'a'], 2: [ 'BB', 'bb'], 4: ['AbbA', 'aBBa']}
res = get_palindrom_dict("AbbAcaBBa")
compare_dictionaries(res, palindrom_dict)

assert check_match("dkoeoerp")
assert not check_match("dkoeomrp")
assert check_match("kdeoeopr")
assert not check_match("kdeoempr")
assert check_match("sdaadd")
assert not check_match("dsaadd")
assert not check_match("chheelcpk")
