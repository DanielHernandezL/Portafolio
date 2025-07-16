import numpy as np
print("Hola mundo")
def grid(plt, im):
    ax = plt.gca()

    m= im.shape[0]
    n= im.shape[1]

    ax.set_xticks(np.arange(0, n, 1))
    ax.set_yticks(np.arange(0, m, 1))

    ax.set_xticklabels(np.arange(0, n, 1))
    ax.set_yticklabels(np.arange(0, m, 1))

    ax.set_xticks(np.arange(-.5, n, 1), minor=True)
    ax.set_yticks(np.arange(-.5, m, 1), minor=True)

    ax.grid(which='minor', color='w', linestyle='-', linewidth=2)