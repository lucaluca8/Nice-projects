import random as rand

n = 10
maxi = 0
nextGen = []
selected = []
population = []
fitness = []

def selection(fitnessSum):
    probabs = []
    global fitness

    #make probabilities for each individual to be selected
    for i in fitness:
        probabs.append(i/fitnessSum)

    #make comulative probabilities
    length = len(probabs)
    s = probabs[0]
    q=[s]
    for i in range(1,length):
        q.append(s)
        s+=probabs[i]

    global selected
    global n
    counter = 0
    pos = 0
    while counter < n//2:

        randNumber = rand.uniform(0,1)
        for i in range(pos,length-1):
            if q[i] <= randNumber and randNumber >= q[i+1]:
                selected.append(population[i+1])
                pos+=1
                break
        counter+=1
    fitness.clear()


def crossOver():
    global selected
    global nextGen
    prob = 0.5
    lenght = len(selected)
    for i in range(lenght-1):
        randNumber = rand.uniform(0,1)
        if randNumber<prob:
            nextGen.append((selected[i][0],selected[i+1][1]))
            nextGen.append((selected[i+1][0], selected[i][1]))
        else:
            nextGen.append(selected[i])
    global  population
    population = nextGen.copy()
    nextGen.clear()

def firstGen():
    for i in range(int(n)):
        x = rand.randint(-20,20)
        y = rand.randint(-5,5)
        population.append((x,y))
    #print("Initial population: ", population)

def calclFitness():
    fitnessSum = 0
    global maxi
    global population

    for indi in population:
        x = indi[0]
        y = indi[1]
        calcFunc = abs(10*x*x*y - 5*x*x - 4*y*y - x*x*x*x - 2*y*y*y*y)/2+1
        if(calcFunc > maxi):
            maxi = calcFunc
        fitness.append(calcFunc)
        fitnessSum = fitnessSum + int(calcFunc)
    #print("Fitness: ", fitness)
    return fitnessSum

def mutate(i):
    mutX = rand.uniform(1,5)
    mutY = rand.uniform(1,3)
    auxI = i[0]
    auxJ = i[1]
    if i[0]>15:
        auxI-=mutX
    else:
        auxI+=mutX
    if i[1]>2.5:
        auxJ-=mutY
    else:
        auxJ+=mutY
    return (auxI,auxJ)


def mutations():
    global population
    #print(population)
    prob = 0.05
    for i in population:
        num = rand.uniform(0,1)
        if num < prob:
            population.pop(population.index(i))
            population.append(mutate(i))
    #print("Mutate: ",population)

def main():
    global n
    global  nextGen
    global selected
    firstGen()
    for i in range(1000):
        fitnessSum = calclFitness()
        #print("Fitness sum: ", fitnessSum)
        selection(fitnessSum)
        crossOver()
        mutations()
    print("Maxim: ", maxi)


if __name__ == main():
    main()