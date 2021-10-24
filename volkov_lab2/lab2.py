import threading
import time

mean_sum = 0


def main(arg):
    nums_list = []
    for i in range(arg):
        num = input('Введите целочисленное значение: ')
        try:
            num = int(num)
        except ValueError:
            raise Exception('Ввели не целочисленное значение!')
        nums_list.append(num)
    print('\n')
    worker_thread = threading.Thread(target=worker, args=(nums_list,))
    worker_thread.start()
    worker_thread.join()
    for num in nums_list:
        if num > mean_sum:
            print('Больше среднего ' + str(num))
            time.sleep(0.007)


def worker(arg):
    sum_list = 0
    odd_list = []
    global mean_sum
    for num in arg:
        sum_list += num
        if num % 2 != 0:
            odd_list.append(num)
        time.sleep(0.012)
    mean_sum = sum_list / len(arg)
    print('Среднее нечетных массива: ' + str(sum(odd_list) / len(odd_list)))


size_of_list = input('Введите размерность массива: ')
try:
    size_of_list = int(size_of_list)
except ValueError:
    raise Exception('Ввели неверную размерность массива')
main_thread = threading.Thread(target=main, args=(size_of_list,))
main_thread.start()
main_thread.join()
