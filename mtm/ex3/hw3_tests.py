import hw3_part1
import hw3_part2


def print_wrong_output(test, expected, test_num):
    print("Failed test " + str(test_num) + " :(")
    print("Your result: " + str(test))
    print("Expected Result: " + str(expected) + "\n")

def tests_3():
    print("\n------------running tests_3 tests------------")
    test1 = hw3_part1.find_best_selling_product("hw3_part1_tests_files/items1.txt")
    test1_expected_result = ('baloon', 5600)
    test2 = hw3_part1.find_k_most_expensive_products("hw3_part1_tests_files/items1.txt", 3)
    test2_expected_result = ['chair', 'lamp', 'pizza']
    test3 = hw3_part1.find_best_selling_product("hw3_part1_tests_files/items2.txt")
    test3_expected_result = ('pineapple', 23200)
    test4 = hw3_part1.find_k_most_expensive_products("hw3_part1_tests_files/items2.txt", 3)
    test4_expected_result = ['banana', 'pineapple', 'bike']
    test5 = hw3_part1.find_best_selling_product("hw3_part1_tests_files/items3.txt")
    test5_expected_result = ('apple', 9500)
    test6 = hw3_part1.find_k_most_expensive_products("hw3_part1_tests_files/items3.txt", 7)
    test6_expected_result = ['apple', 'banana', 'bike', 'chair', 'lamp', 'phone', 'pineapple']
    test7 = hw3_part1.find_best_selling_product("hw3_part1_tests_files/items4.txt")
    test7_expected_result = ('pizza', 43350)
    test8 = hw3_part1.find_k_most_expensive_products("hw3_part1_tests_files/items4.txt", 7)
    test8_expected_result = ['apple', 'baloon', 'pizza', 'bike', 'pineapple', 'phone', 'chair']
    test9 = hw3_part1.find_best_selling_product("hw3_part1_tests_files/items5.txt")
    test9_expected_result = ('', 0)
    test10 = hw3_part1.find_k_most_expensive_products("hw3_part1_tests_files/items5.txt", 3)
    test10_expected_result = []
    test11 = hw3_part1.find_best_selling_product("hw3_part1_tests_files/items6.txt")
    test11_expected_result = ('bike', 52200)
    test12 = hw3_part1.find_k_most_expensive_products("hw3_part1_tests_files/items6.txt", 7)
    test12_expected_result = ['apple', 'lamp', 'bike', 'banana', 'chair', 'pineapple', 'phone']

    results = [
        test1 == test1_expected_result,
        test2 == test2_expected_result,
        test3 == test3_expected_result,
        test4 == test4_expected_result,
        test5 == test5_expected_result,
        test6 == test6_expected_result,
        test7 == test7_expected_result,
        test8 == test8_expected_result,
        test9 == test9_expected_result,
        test10 == test10_expected_result,
        test11 == test11_expected_result,
        test12 == test12_expected_result
    ]

    if(test1 == test1_expected_result):
        print("Passed test 1!\n")
    else:
        print_wrong_output(test1, test1_expected_result, 1)

    if(test2 == test2_expected_result):
        print("Passed test 2!\n")
    else:
        print_wrong_output(test2, test2_expected_result, 2)

    if(test3 == test3_expected_result):
        print("Passed test 3!\n")
    else:
        print_wrong_output(test3, test3_expected_result, 3)

    if(test4 == test4_expected_result):
        print("Passed test 4!\n")
    else:
        print_wrong_output(test4, test4_expected_result, 4)

    if(test5 == test5_expected_result):
        print("Passed test 5!\n")
    else:
        print_wrong_output(test5, test5_expected_result, 5)

    if(test6 == test6_expected_result):
        print("Passed test 6!\n")
    else:
        print_wrong_output(test6, test6_expected_result, 6)

    if(test7 == test7_expected_result):
        print("Passed test 7!\n")
    else:
        print_wrong_output(test7, test7_expected_result, 7)

    if (test8 == test8_expected_result):
        print("Passed test 8!\n")
    else:
        print_wrong_output(test8, test8_expected_result, 8)

    if (test9 == test9_expected_result):
        print("Passed test 9!\n")
    else:
        print_wrong_output(test9, test9_expected_result, 9)

    if (test10 == test10_expected_result):
        print("Passed test 10!\n")
    else:
        print_wrong_output(test10, test10_expected_result, 10)

    if (test11 == test11_expected_result):
        print("Passed test 11!\n")
    else:
        print_wrong_output(test11, test11_expected_result, 11)

    if (test12 == test12_expected_result):
        print("Passed test 12!\n")
    else:
        print_wrong_output(test12, test12_expected_result, 12)

    if all(results):
        print("You passed all the tests!")
    else:
        print("You passed " + str(results.count(True)) + "/" + str(len(results)) + " of the tests")


    print("\n\n")

    tests1 = {
        "AbbAcaBBa": {1: ['A', 'b', 'b', 'A', 'c', 'a', 'B', 'B', 'a'], 2: ['bb', 'BB'], 4: ['AbbA', 'aBBa']},
        "aaaaaa": {1: ['a', 'a', 'a', 'a', 'a', 'a'], 3: ['aaa', 'aaa', 'aaa', 'aaa'], 5: ['aaaaa', 'aaaaa'], 2: ['aa', 'aa', 'aa', 'aa', 'aa'], 4: ['aaaa', 'aaaa', 'aaaa'], 6: ['aaaaaa']},
        "ababababa": {1: ['a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a'], 3: ['aba', 'bab', 'aba', 'bab', 'aba', 'bab', 'aba'], 5: ['ababa', 'babab', 'ababa', 'babab', 'ababa'], 7: ['abababa', 'bababab', 'abababa'], 9: ['ababababa']},
        "AbcAbcbaBa": {1: ['A', 'b', 'c', 'A', 'b', 'c', 'b', 'a', 'B', 'a'], 3: ['bcb', 'aBa']},
        "AbcDefgHgfeDcbA": {1: ['A', 'b', 'c', 'D', 'e', 'f', 'g', 'H', 'g', 'f', 'e', 'D', 'c', 'b', 'A'], 3: ['gHg'], 5: ['fgHgf'], 7: ['efgHgfe'], 9: ['DefgHgfeD'], 11: ['cDefgHgfeDc'], 13: ['bcDefgHgfeDcb'], 15: ['AbcDefgHgfeDcbA']}
    }

    tests2 = {
        "dkoeoerp": True,
        "ctaptmapld": True,
        "sdaadd": True,
        "dsaadd": False,
        "abababab": True,
        "ababababa": False,
        "aabbccddeeffgg": True,
        "aabbccddeeffgh": True,
        "aabbccddeeffgf": True,
        "": True
    }

    count_tests1 = 0
    for test, expected_result in tests1.items():
        result = hw3_part2.get_palindrom_dict(test)
        if result == expected_result:
            print("Passed test for str: " + test)
            count_tests1 += 1
        else:
            print("Failed test for str: " + test)
            print("Your result:\n" + str(result))
            print("Expected result:\n" + str(expected_result))
        print()

    if count_tests1 == len(tests1):
        print("You passed all 3.1 tests!")
    else:
        print("You passed " + str(count_tests1) + "/" + str(len(tests1)) + " of the 3.1 tests")

    print("\n\n")

    count_tests2 = 0
    for test, expected_result in tests2.items():
        result = hw3_part2.check_match(test)
        if result == expected_result:
            print("Passed test for str: " + test)
            count_tests2 += 1
        else:
            print("Failed test for str: " + test)
            print("Your result:\n" + str(result))
            print("Expected result:\n" + str(expected_result))
        print()

    if count_tests2 == len(tests2):
        print("You passed all 3.2 tests!")
    else:
        print("You passed " + str(count_tests2) + "/" + str(len(tests2)) + " of the 3.2 tests")

    print()
    if (all(results) and count_tests1 == len(tests1) and count_tests2 == len(tests2)):
        print("CONGRATULATIONS! You passed all part 1 and part 2 tests!")
