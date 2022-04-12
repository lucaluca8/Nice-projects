import random as rand

n = 1000
maxi = 0
nextGen = []
selected = []
population = []
fitness = []
xMax = 0
yMax = 0
avrMax1 = 0
avrMax2 = 1


def selection(fitnessSum):
    probabs = []
    global fitness

    # make probabilities for each individual to be selected
    for i in fitness:
        probabs.append(i / fitnessSum)

    # make comulative probabilities
    length = len(probabs)
    s = probabs[0]
    q = [s]
    for i in range(1, length):
        q.append(s)
        s += probabs[i]

    global selected
    global n
    counter = 0
    pos = 0
    while counter < n:
        randNumber = rand.uniform(0, 1)
        for i in range(pos, length - 1):
            if q[i] <= randNumber and randNumber <= q[i + 1]:
                selected.append(population[i + 1])
                pos += 1
                break
        counter += 1
    fitness.clear()
    print("Population in selection: ", population)


def crossOver():
    global selected
    global population
    nextGen = []
    prob = 0.5
    lenght = len(selected)
    for i in range(lenght - 1):
        randNumber = rand.uniform(0, 1)
        if randNumber < prob:
            nextGen.append((selected[i][0], selected[i + 1][1]))
            nextGen.append((selected[i + 1][0], selected[i][1]))
        else:
            nextGen.append(selected[i])
            nextGen.append(selected[i + 1])


    population = nextGen.copy()
    nextGen.clear()
    selected.clear()


def firstGen():
    global population
    for i in range(int(n)):
        x = rand.uniform(1, 3)
        y = rand.uniform(1, 3)
        population.append((x, y))
    print("Initial population: ", population)


def calclFitness():
    fitnessSum = 0
    global maxi
    global population
    global xMax
    global yMax
    global avrMax1
    global avrMax2
    maxim = 0
    for indi in population:
        x = indi[0]
        y = indi[1]
        calcFunc = ((1 / 2) * (x + y) - 1) / ((x * x) + (y * y))
        if (calcFunc > maxim):
            maxim = calcFunc
            if avrMax1 == 0:
                avrMax1 = maxim
            else:
                avrMax2 = avrMax1
                avrMax1 = maxim
        fitness.append(calcFunc)
        fitnessSum = fitnessSum + calcFunc
        if maxim > maxi:
            xMax = x
            yMax = y
            maxi = maxim
    print("Fitness: ", fitness)
    return fitnessSum


def mutate(i):
    mutX = rand.uniform(0, 1)
    mutY = rand.uniform(0, 1)
    auxI = i[0]
    auxJ = i[1]
    if i[0] > 2:
        auxI -= mutX
    else:
        auxI += mutX
    if i[1] > 2:
        auxJ -= mutY
    else:
        auxJ += mutY
    return (auxI, auxJ)


def mutations():
    global population
    print("Population in mutation: ", len(population))
    prob = 0.01
    for i in population:
        num = rand.uniform(0, 1)
        if num < prob:
            population.append(mutate(i))
            population.pop(population.index(i))

    print("Mutate: ", len(population))


def main():
    global n
    global nextGen
    global selected
    global xMax
    global yMax
    global avrMaxPre
    global avrMaxPost
    firstGen()
    genCt = 0
    while abs(avrMax1 - avrMax2) > 0.0000001:
        fitnessSum = calclFitness()
        print("Fitness sum: ", fitnessSum)
        selection(fitnessSum)
        crossOver()
        mutations()
        genCt +=1
        print()
        print()
    print("X Max: ", xMax)
    print("Y Max: ", yMax)
    print("Maxim: ", maxi)
    print("Generations: ",genCt)


if __name__ == main():
    main()