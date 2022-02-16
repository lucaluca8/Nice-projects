#librariile utilizate
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

#inputul initial

choice=int(input("Apasa 1 daca doresti graf orientat sau 2 daca doresti graf neorientat: ")) #aleg daca doresc graf orientat sau neorientat
nrNoduri=int(input("Introduceti numarul de noduri: ")) #aleg cate noduri imi doresc sa aiba graful initial

#Functii care formeaza graful orientat/neorientat

def GrafOrientat(nrNoduri):
    G=nx.DiGraph(directed=True)
    print("Introduce-ti nodurile: ")
    while nrNoduri != 0:
        x=int(input())
        G.add_node(x)
        nrNoduri=nrNoduri-1
    print("Introduce-ti arcele,apasati x pentru opri introducerea de arce: ")
    while True:
        a=input()
        if a == 'x':
            break
        b=input()
        if b == 'x':
            break
        if a in G and b in G:
            G.add_edge(a,b)
        else:
            print("Aceasta muchie nu poate fi adaugata")
    return G


def GrafNeorientat(nrNoduri):
    G=nx.Graph(directed=False)
    print("Introduce-ti nodurile: ")
    while nrNoduri != 0:
        x = input()
        G.add_node(x)
        nrNoduri = nrNoduri - 1
    print("Introduce-ti arcele,apasati x pentru opri introducerea de arce: ")
    while True:
        a = input()
        if a == 'x':
            break
        b = input()
        if b == 'x':
            break
        if a in G and b in G:
            G.add_edge(a,b)
            G.add_edge(b,a)
        else:
            print("Acesta nu poate fi un arc")
    return G

if choice == 1:
    G=GrafOrientat(nrNoduri)
else:
    G=GrafNeorientat(nrNoduri)


#Afisarea grafului cu o librarie grafica si salvarea in fisier a matricei de adiacenta

def PrintGraph(G):
    pos = nx.spring_layout(G)
    nx.draw_networkx(G,pos,with_labels = True)
    plt.show()

PrintGraph(G)

matrix=nx.to_numpy_matrix(G)

print(matrix)
def SalveazaMatriceaCaTXT(matrix):
    file1=open("Matrice_de_adiacenta.txt","w+")
    file1.write(str(nrNoduri)+'\n')
    for line in matrix:
        np.savetxt(file1,line,fmt ='%i')
    file1.close()

SalveazaMatriceaCaTXT(matrix)

#Daca utilizatorul isi doreste sa mai faca modificari la graful initial

print("Ati salvat si afisat graful initial. Doriti sa mai modificati ceva? Apasati 1 daca da si 2 daca nu: ")
modifiy_choice=int(input())

def ModificaGrafOrientat(G):
    print("Doriti sa adaugati mai multe noduri? Introduceti 1 daca da si 2 daca nu: ")
    nod_add=int(input())
    if nod_add == 1:
        print("Introduce-ti x cand doriti sa va opriti din a adauga noduri: ")
        while True:
            a=input()
            if a == 'x':
                break
            if not a in G:
                G.add_node(a)
            else:
                print("Acest nod deja exista. Incercati din nou: ")
        
        print("Doriti sa adaugati mai multe muchii? Introduceti 1 daca da si 2 daca nu: ")
        edge_add=int(input())
        if edge_add == 1:
            print("Introduce-ti x cand doriti sa va opriti din a adauga noduri: ")
            while True:
                a=input()
                if a == 'x':
                    break
                b=input()
                if b == 'x':
                    break
                if a in G and b in G:
                    G.add_edge(a,b)
        return G


def ModificaGrafNeorientat(G):
    print("Doriti sa adaugati mai multe noduri? Introduceti 1 daca da si 2 daca nu: ")
    nod_add = int(input())
    if nod_add == 1:
        print("Introduce-ti x cand doriti sa va opriti din a adauga noduri: ")
        while True:
            a = input()
            if a == 'x':
                break
            if not a in G:
                G.add_node(a)
            else:
                print("Acest nod deja exista. Incercati din nou: ")
        
        print("Doriti sa adaugati mai multe muchii? Introduceti 1 daca da si 2 daca nu: ")
        edge_add = int(input())
        if edge_add == 1:
            print("Introduce-ti x cand doriti sa va opriti din a adauga noduri: ")
            while True:
                a = input()
                if a == 'x':
                    break
                b = input()
                if b == 'x':
                    break
                if a in G and b in G:
                    G.add_edge(a, b)
                    G.add_edge(b,a)
        return G
    
while True:
    if modifiy_choice == 1:
        if choice == 1:
            G=ModificaGrafOrientat(G)
        else:
            G=ModificaGrafNeorientat(G)

    print("Daca doriti sa afisati noul graf apasati tasta 1: ")
    print_choice=int(input())
    if print_choice == 1:
        PrintGraph(G)
    print("Daca doriti sa salvati matricea de adiacenta a noului graf apasati tasta 1: ")
    save_choice=int(input())
    if save_choice == 1:
        matrix = nx.to_numpy_matrix(G)
        SalveazaMatriceaCaTXT(matrix)
    print("Daca doriti sa nu mai faceti modificari la graf apasati tasta 2. Daca doriti sa continuati sa modificati graful apasati 1: ")
    continue_modify=int(input())
    if continue_modify == 2:
        break