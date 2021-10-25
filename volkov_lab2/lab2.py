import threading
import time

# Вариант 6, Колесников Иван

# Объявляем глобально среднее арифметическое
mean_sum = 0

# Поток main отвечает за нахождение min, max и количество значений больше среднего, args - передаваемое в поток для объявления размерности
def main(arg):
    # Объявляем массив для заполнения
    nums_list = []
    # Цикл отвечающий за заполнение массива и валидацию входных переменных
    for i in range(arg):
        num = input('Введите целочисленное значение: ')
        try:
            num = int(num)
        except ValueError:
            raise Exception('Ввели не целочисленное значение!')
        nums_list.append(num)
    print('\n')
    # Объявляем поток, который вызывает функцию worker, передаем в нее наш массив
    worker_thread = threading.Thread(target=worker, args=(nums_list,))
    # Запускаем поток worker
    worker_thread.start()
    num_min = nums_list[0] # Минимальное
    num_max = nums_list[0] # Максимальное
    # Цикл находящий минимальное и максимальное, проходя по всему массиву, со сном в 100 мс
    for num in nums_list:
        if num > num_max:
            num_max = num
        if num < num_min:
            num_min = num
        time.sleep(0.1)
        print('Минимальный: ' + str(num_min) + '\nМаксимальный: ' + str(num_max))
    # Ждем окончания потока worker
    worker_thread.join()
    # Объявляем массив для получения количества чисел массива больше среднего
    bigger_then_mean = []
    # Цикл находящий количество числе массива, которые больше среднего
    for num in nums_list:
        if num > mean_sum:
            bigger_then_mean.append(num)
            time.sleep(0.007)
    print('Количество больше среднего: ' + str(len(bigger_then_mean)))
    print('**main_thread finished**')


# Процесс worker находящий среднее исходного массива nums_list
# и нового массива od_list четных элементов, arg - передаем nums_list
def worker(arg):
    # Переменна для нахождения суммы элементов массива
    sum_list = 0
    # Задаем массив четных элементов
    od_list = []
    # Обращаемся глобально к переменной mean_sum для ее изменения
    global mean_sum
    # Цикл, проходящий по элементам массива, находящий их сумму и проверяющий на четность.
    # Если четный - добавляем в od_list
    for num in arg:
        sum_list += num
        if num % 2 == 0:
            od_list.append(num)
        time.sleep(0.07)
    # Находим среднее арифметическое nums_list
    mean_sum = sum_list / len(arg)
    print('Среднее массива: '+ str(mean_sum))
    print('Среднее четных массива: ' + str(sum(od_list) / len(od_list)))
    print('**worker_thread finished**')

# Задаем размерность массива и валидируем на int
size_of_list = input('Введите размерность массива: ')
try:
    size_of_list = int(size_of_list)
except ValueError:
    raise Exception('Ввели неверную размерность массива!')
# Объявляем поток, который вызывает функцию main, передаем в нее размерность size_of_list
main_thread = threading.Thread(target=main, args=(size_of_list,))
# Запускаем поток main_thread
main_thread.start()
# Ожидаем окончания main_thread
main_thread.join()
