#include <iostream>
using namespace std;

struct Aluno {
    string nome;
    string cpf;
    int idade;
};

struct NoArvore {
    Aluno aluno;
    NoArvore* esquerda;
    NoArvore* direita;
    int key;
};

NoArvore* inserirAlunoBST(NoArvore*& raiz, Aluno aluno, int key) {
    if (raiz == NULL) {
        raiz = new NoArvore;
        raiz->aluno = aluno;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->key = key;
    } else {
        if (key > raiz->key) {
            raiz->direita = inserirAlunoBST(raiz->direita, aluno, key);
        } else if (key < raiz->key) {
            raiz->esquerda = inserirAlunoBST(raiz->esquerda, aluno, key);
        }
    }

    return raiz;
}

void percorrerEmOrdem(NoArvore* raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        cout << "Nome: " << raiz->aluno.nome << "\nCPF: " << raiz->aluno.cpf << "\nIdade: " << raiz->aluno.idade << endl;
        cout << "-------------------------" << endl;
        percorrerEmOrdem(raiz->direita);
    }
}

void buscaAlunoBST(NoArvore *&raiz, int key) {
    NoArvore* resultado = NULL;

    while (raiz != NULL && raiz->key != key) {
        if (key < raiz->key) {
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }

    if (raiz != NULL) {
        cout << "Aluno encontrado:" << endl;
        cout << "Nome: " << raiz->aluno.nome << "\nCPF: " << raiz->aluno.cpf << "\nIdade: " << raiz->aluno.idade << endl;
        cout << "-------------------------" << endl;

    } else {
        cout << "Aluno com chave " << key << " nao encontrado." << endl;
    }
}

NoArvore* removerAlunoBST(NoArvore *&raiz, int key) {
    if (raiz == NULL) {
        return raiz;
    }

    if (key < raiz -> key) {
        raiz -> esquerda = removerAlunoBST(raiz -> esquerda, key);
        
    } else if (key > raiz -> key) {
        raiz -> direita = removerAlunoBST(raiz -> direita, key);
    } else {
        if (raiz -> esquerda == NULL && raiz->direita == NULL ) {
            delete raiz;
            raiz = NULL;
            return raiz;
            
        } else if (raiz -> esquerda == NULL) {
            NoArvore *aux = raiz;
            
            raiz = raiz -> direita;
			delete aux;
			
			return raiz;
			
        } else if(raiz -> direita == NULL){
        	NoArvore *aux = raiz;
			
			raiz = raiz -> esquerda;
			delete aux;
			
			return raiz;
			
		} else {
			NoArvore *aux = raiz -> esquerda;
			
			while(aux -> direita != NULL) {
				aux = aux -> direita;
			}
			
			raiz -> key = aux -> key;
			raiz -> esquerda = removerAlunoBST(raiz -> esquerda, raiz -> key);
		}
	}
	
	return raiz;
}
			
bool verificarBST(NoArvore* raiz, int minimo, int maximo) {
    if (raiz == NULL) {
        return true;
    }

    if (raiz->key < minimo || raiz->key > maximo) {
        return false;
    }

    return verificarBST(raiz->esquerda, minimo, raiz->key - 1) && verificarBST(raiz->direita, raiz->key + 1, maximo);
}
int main(int argc, char** argv) {
    NoArvore* raiz = NULL;

    Aluno aluno1 = {"Dawyla", "1234", 19};
    Aluno aluno2 = {"Jordy", "5678", 25};
    Aluno aluno3 = {"Leontev", "91011", 22};

    raiz = inserirAlunoBST(raiz, aluno1, 1);
    raiz = inserirAlunoBST(raiz, aluno2, 2);
    raiz = inserirAlunoBST(raiz, aluno3, 3);

    percorrerEmOrdem(raiz);
    
    cout << endl ;

    buscaAlunoBST(raiz, 2);
   
   	cout << endl;
    removerAlunoBST(raiz, 1);
    
    percorrerEmOrdem(raiz);
    
    if (verificarBST(raiz, INT_MIN, INT_MAX)) {
        cout << "A arvore eh uma BST." << endl;
    } else {
        cout << "A arvore nao eh BST." << endl;
    }


    return 0;
}

