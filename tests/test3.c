#include <stdlib.h>

int main() {
    int ret;

    // Exécuter le script Python
    ret = system("python script.py");

    if(ret == -1) {
        // Gérer l'erreur
    }

    return 0;
}
