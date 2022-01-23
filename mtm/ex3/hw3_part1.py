def parser(line, products_dict):
    array = line.split(' ')
    array[-1] = array[-1].replace("\n", "")

    if array[0] == "add":
        products_dict = add_product(products_dict, array[2], float(array[3]), float(array[4]))

    elif array[0] == "change":
        products_dict = change_amount(products_dict, array[2], float(array[3]))

    elif array[0] == "ship":
        i_prod = 2
        while i_prod + 2 <= len(array):
            name = array[i_prod].replace(',', '')
            amount = array[i_prod + 1]
            products_dict = ship_order(products_dict, name, float(amount))
            i_prod += 3
    return products_dict


# Press the green button in the gutter to run the script.
def read_file(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    products_dict = {}
    if lines == "":
        return -1
    else:
        for li in lines:
            products_dict = parser(li, products_dict)

    return products_dict


def add_product(products_dict, name, price, amount):
    if float(price) < 0 or float(amount) < 0 or name in products_dict:
        return products_dict

    products_dict[name] = [price, amount, 0]
    return products_dict


def change_amount(products_dict, name, amount):
    if name not in products_dict:  # or (dict[name]+amount<0):
        return products_dict

    products_dict[name][1] += amount
    return products_dict


def ship_order(products_dict, name, amount):
    if name in products_dict and products_dict[name][1] - amount >= 0 and amount >= 0:
        products_dict[name][1] -= amount
        products_dict[name][2] += amount  # The [2] parameter is the counter of the sold products

    return products_dict


def find_k_most_expensive_products(file_name, k):
    products_dict = read_file(file_name)
    expensive_products = []
    if k <= 0:
        return expensive_products
    if k > len(products_dict):
        k = len(products_dict)
    for i in range(k):
        if products_dict == {}:
            break
        max_value = 0
        max_index = 0
        for j, l in products_dict.items():
            if max_value < l[0] or (max_value == l[0] and j < max_index):
                max_value = l[0]
                max_index = j
        expensive_products.append(max_index)
        del products_dict[max_index]

    return expensive_products


def find_best_selling_product(filename):
    products_dict = read_file(filename)
    best_seller_name = ""
    if products_dict == -1:
        return tuple(("", 0))
    price = 0
    profit = 0
    for name, l in products_dict.items():
        profit = l[2] * l[0]
        if price < profit:
            price = profit
            best_seller_name = name
        elif price == profit:
            if name < best_seller_name:
                best_seller_name = name

    return tuple((best_seller_name, price))
