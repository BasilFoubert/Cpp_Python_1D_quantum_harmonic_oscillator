import numpy as np
import matplotlib.pyplot as plt
import csv
import sys

# Vérifie si l'utilisateur a fourni le chemin du fichier
if len(sys.argv) < 2:
    print("Veuillez fournir le chemin du fichier en argument.")
    sys.exit()

file_path = sys.argv[1]

# Lire la matrice à partir du fichier CSV
matrix = []
with open(file_path, 'r') as file:
    csv_reader = csv.reader(file)
    for row in csv_reader:
        matrix.append([float(value) for value in row])

matrix = np.array(matrix)

# Afficher la matrice comme une image 2D
plt.imshow(matrix, aspect='equal', cmap='hot') # 'hot' est un exemple de colormap
plt.colorbar() # Ajoute une barre de couleur pour indiquer l'échelle
plt.xlabel('X-values')
plt.ylabel('Z-values')
plt.title('Densité Nucléaire')

# Sauvegarder la figure dans un fichier PNG
plt.savefig("visu2D.png")

#plt.show()
