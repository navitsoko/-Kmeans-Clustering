import math
import sys


# opens the file by name and transfer the points from string to a list
# return list of points(list of lists)
def reader(filename):
    point_list = []
    with open(filename) as f:
        i = 0
        line = f.readline()
        while line != "":
            point_list.append(line.split(","))
            point_list[i][len(point_list[i]) - 1] = point_list[i][len(point_list[i]) - 1][:len(point_list[i][len(point_list[i]) - 1])-1]
            i += 1
            line = f.readline()
    return point_list


# messures the euclidian distance between two points
def euclidian_dist(p1, p2):
    sum = 0
    for i in range(len(p1)):
        newp1 = float(p1[i])
        newp2 = float(p2[i])
        sum += (newp1 - newp2) ** 2
    return math.sqrt(sum)


# classify each point in points_list to his closest clustre then sending the new list of lists of points to sum_points_by_cor
# and returns it
def cur_points_by_cor(array_means, points_list, k):
    curr_list = [[] for i in range(k)]
    for point in points_list:
        min_length = euclidian_dist(point, array_means[0])
        min_mean_index = 0
        for mean_index in range(len(array_means)):
            temp = euclidian_dist(point, array_means[mean_index])
            if (temp < min_length):
                min_mean_index = mean_index
                min_length = temp

        curr_list[min_mean_index].append(point)
    return sum_points_by_cor(curr_list, k)


# calculate the new means of the list from cur_points_by_cor and returns it.
def sum_points_by_cor(Dlist, k):
    sum_list = [[0 for i in range(len(Dlist[0][0]))] for p in range(k)]
    for j in range(k):
        for point in Dlist[j]:
            for i in range(len(point)):
                sum_list[j][i] += float(point[i])

    for h in range(k):
        for r in range(len(Dlist[0][0])):
            sum_list[h][r] = float(sum_list[h][r]) / len(Dlist[h])
    return sum_list


# iniitiate the first means
def initialize(k, points_list):
    array_means = [j for j in points_list[:k]]
    return array_means


# checks if we can continue in the while loop
def epsilon_flag(array_old, array_new, eps):
    for i in range(len(array_old)):
        for j in range(len(array_old[0])):
            if (abs(float(array_old[i][j]) - float(array_new[i][j])) >= eps):
                return False
    return True


# our main, making the new means every time and looping it till we get to iter or the
# abs(old_means-new_means)<epsilon
def final(k, eps, points_list, iter=200):
    i = 0
    array_means = initialize(k, points_list)
    array_sums = cur_points_by_cor(array_means, points_list, k)
    while not epsilon_flag(array_means, array_sums, eps) or i <= iter:
        array_means = array_sums
        array_sums = cur_points_by_cor(array_means, points_list, k)
        i += 1
    return array_means


def is_k_valid(k, points_list):
    return ((k % 1 == 0) and (k > 1) and (k < len(points_list)))

def is_iter_valid(iter):
    return (iter%1==0) and (iter>1) and (iter<1000)


if len(sys.argv)>4 or len(sys.argv) < 3:
        print("An Error Has Occurred")
elif not sys.argv[1].isnumeric():
    print("Invalid number of clusters!")
elif len(sys.argv) == 4 and not sys.argv[2].isnumeric():
            print("Invalid maximum iteration!")
else:         
    k = float(sys.argv[1])
    if len(sys.argv) == 4:
        iter = float(sys.argv[2])
        filename = sys.argv[3]
    else:
        iter = 200
        filename = sys.argv[2]
    points_list = reader(filename)
    if is_k_valid(k,points_list) and is_iter_valid(iter):
        iter = int(iter)
        k = int(k)
        array_means = final(k, 0.001, points_list, iter)
        for t in range(len(array_means)):
            y = 0
            for j in array_means[t]:
                if y == len(array_means[t]) - 1:
                    print('%.4f' % j, end="")
                else:
                    print('%.4f' % j + ",", end="")
                y += 1
            print()
    else:
        if not is_iter_valid(iter):
            print("Invalid maximum iteration!")
        if not  is_k_valid(k,points_list):
            print("Invalid number of clusters!")
