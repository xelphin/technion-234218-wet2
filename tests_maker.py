import random
def auto_tester():
    test_string = ""
    for i in range(1000):
        test_string += "add team " + str(random.randint(0, 100)) + "\n"
    #overwriting file:
    f = open("matan_tests\\test1.txt", "w")
    f.write(test_string)
    f.close()

if __name__ == '__main__':
    auto_tester()