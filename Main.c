#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.c"

//qst5
struct node1 {
    int data;
    struct node1 *left, *right;
};


//------------------------------------recursive---------------------------------------------------------------------------------------
// ----------------------------------------qst1 recursive

int equalBTreesRecu(BTree bt1, BTree bt2){ 
	if(isEmptyBTree(bt1))//si bt1 vide alors faux
		return (isEmptyBTree(bt2));
	else
		if(isEmptyBTree(bt2))
			return 0;
		else return root(bt1)==root(bt2) && equalBTreesRecu(leftChild(bt1),leftChild(bt2)) && equalBTreesRecu(rightChild(bt1),rightChild(bt2));
}



//---------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------qst2 recursive
int isSubBTreeRecu(BTree sbt, BTree bt){ 
	if(isEmptyBTree(bt))
		return isEmptyBTree(sbt);
	else 
		if(equalBTreesRecu(sbt,bt))//incerementer sbt f equal
			return 1;
		else return isSubBTreeRecu(sbt,leftChild(bt)) || isSubBTreeRecu(sbt,rightChild(bt));
}






//-----------------------------------------------------------iterative----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------


//--------------------------------------------qst1 iterative
// Iterative pour voir si deux arbre sont egaux
int isIdentical(Node* x, Node* y)
{
	// if both trees are empty, return true
	if (x == NULL && y == NULL) {//si les noeud sont nul return 1
		return 1;
	}

	// si premier arbre vide et arbre 2 non on retourne faux
	if (x == NULL) {
		return 0;
	}

	// bt1 non vide et bt2 vide donc retourner faux
	if (y == NULL) {
		return 0;
	}

	// create a stack to hold `Node*` pairs
     // creation d'une pile de capacité 15
	struct stack *pt = newStack(15);
     push(pt, x);//on enfile x et y
     push(pt, y);

	// tq pile non vide
	while (!isEmpty(pt))
	{
		// pop the top pair from the stack and process it
		Node* x = pop(pt);//deempiler de la pile
		Node* y = pop(pt);

		if (x->elem != y->elem) {//je compare les deux element si different retourner faux
			return 0;
		}

		// if the left subtree of both `x` and `y` exists, push their addresses
		// to stack; otherwise, return false if only one left child exists
		if (x->left && y->left) {
               push(pt, x->left);
               push(pt, y->left);
		}
		else if (x->left || y->left) {// si un arbre a un fils gauche l'autre non je sors directement
			return 0;
		}

		// if the right subtree of both `x` and `y` exists, push their addresses
		// to stack; otherwise, return false if only one right child exists
		if (x->right && y->right) {// si un arbre a un fils droit l'autre non je sors directement
			push(pt, x->right);
               push(pt, x->right);
		}
		else if (x->right || y->right) {
			return 0;
		}
	}

	return 1;
}




//-----------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------qst2 iterative

int subTree(Node *n1, Node *n2)
{
    Node *stack1[200], *stack2[200];  // la declaration d un tableau pointeur
    int size1 = 0, size2 = 0;
    Node *p1, *p2;  // deux pointeur pour parcourir les 2 arbres
    //ajouter racine a partir de la racine on fait le parcours infixé
    //on prend la racine du petit arbre on comparre par rapport a la racine du second , j'ai fait le cas ou les de sous arbre commence par la meme racine , je doit rajouter une recherche de la racone du sous arbre dans l'arbre
    for (p1 = n1; p1 != NULL; p1 = p1->left) {
        stack1[size1++] = p1;
    }
    for (p2 = n2; p2 != NULL; p2 = p2->left) {
        stack2[size2++] = p2;
    }
    
    while (size1 > 0) {
    	//depilement
        Node *n1 = stack1[--size1]; // desempiler
        Node *n2 = stack2[--size2]; // desempiler
        //comparaison
        if(n1->elem != n2->elem){//si ya un element de bt1 n'est pas dans bt2 on dit que pas sous arbre
        	//printf("**bt1 n'est pas un sous arbre de bt2.\n");
        	return 0;
        }
         
        //passer au element suivant //empiler
        for (p1 = n1->right; p1 != NULL; p1 = p1->left) {//infixé par a right puis elle parcours les fils gauches (R,Fg,FD)
            stack1[size1++] = p1;
        }
        for (p2 = n2->right; p2 != NULL; p2 = p2->left) {
            stack2[size2++] = p2;
        }
    }
    //printf("bt1 est un sous arbre de bt2.\n");
    return 1;
}


//appel a la fonction
int IssubBTreesIter(Node *t1, Node *t2)
{
    return subTree(t1, t2);
}





//------------------------------------------------Verification 02------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------qst3 iteative
int findElem(Node *n, int e)
{
    Node *stack[100];
    int stack_size = 0;
    Node *p;
    
    for (p = n; p != NULL; p = p->left) {
        stack[stack_size++] = p;
    }
    
    while (stack_size > 0) {
        Node *n = stack[--stack_size]; // pop
        
        if(n->elem == e)
        {
        	printf(" \t %d appartient a l'arbre bt1.\n", e);
            return 1;
		}
         
        
        for (p = n->right; p != NULL; p = p->left) {
            stack[stack_size++] = p;
        }
       
    }
    printf("\t %d n'appartient pas a l'arbre bt1.\n", e);
    return 0;
}

int findElemIter(Node *t, int e)
{
    return findElem(t, e);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------qst3 recursive
int findElemRec(BTree bt,Element e){
	if(isEmptyBTree(bt))
		return 0;
	else {
		if(root(bt)==e)//si element egal a la racine
			return 1;
		else
			return findElemRec(leftChild(bt),e) ||  findElemRec(rightChild(bt),e);
	}
}




//------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------qst4 recursive
Element findMinRec(BTree bt){
	if(isEmptyBTree(bt))
		printf("finfMin impossible!");
	if(isLeaf(bt))
	 	return root(bt);
	else {
		Element m=root(bt);
		if(!isEmptyBTree(leftChild(bt)))
			m=min(m,findMinRec(leftChild(bt)));
		if(!isEmptyBTree(rightChild(bt)))
			m=min(m,findMinRec(rightChild(bt)));
		
		return m;
	}
}
//------------------------------------------------------------------------------------------------
//----------------------------------------------------qst 04 iterative
int findMin(Node *n)
{
    Node *stack[100];
    int stack_size = 0, min;
    Node *p;
    
    for (p = n; p != NULL; p = p->left) {
        stack[stack_size++] = p;
    }
    Node *m = stack[stack_size];
    min = m->elem;
    while (stack_size > 0) {
       Node *n = stack[--stack_size]; // pop
        
        if(n->elem < min)
        {
        	min = n->elem;
		}
         
        for (p = n->right; p != NULL; p = p->left) {
            stack[stack_size++] = p;
        }
       
    }
    printf("\t Le minimum de l'arbre: %d\n",min);
    return 1;
}

int findMinIter(Node *t)
{
    return findMin(t);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------qst5 iteraive
void largeur(BTree R){
	file *f;
	BTree x;
    initfile(&f);//initialisation de la file
	enfiler(&f,R);//enfiler mon arbre initial dans la file
	while(filevide(f)==0){ //tq non file vide
		defiler(&f,&x); //on defile
		printf("%d ,", x->elem);//on ecrit l'element
		if((x->left) !=NULL){
			enfiler(&f,x->left); //puis on passe au fils gauche s'il existe
		}
		if((x->right) !=NULL){//puis fils droit
			enfiler(&f,x->right);
		}
	}
}
//------------------------------------------------------------------------------------------------------------------
//----------------------------------------------qst5 recursive
 
/* fait une boucle pour afficher tout les niveau de l'arbre grace a une boucle sur la fonction print level*/
void printLevelOrder( Node *root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}
 
// tu donne le niveau elle affiche le contenu qui a dans ce niveau
void printCurrentLevel(Node *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)//affichage quand on arrive a un 1 , noeud ywelli racine
        printf("%d ", root->elem); 
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}
 
//calculer la hauteur de l'arbre a partir de la racine jusqu'au feuille
int height(Node* nodee)
{
    if (nodee == NULL)
        return 0;
    else {
        /* calculer la hauteur de chaque sous arbre */
        int lheight = height(nodee->left);
        int rheight = height(nodee->right);
 
        /* utiliser le sous arbre le plus grand */
         if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

int main(){
     // la declaration de deux arbres
     BTree bt1=NULL, bt2=NULL, bt3=NULL;
     Element sommet;

     //la creation de la premiere arbre
     addNode(&bt1, 20);
     addNode(&bt1, 10);
     addNode(&bt1, 5);
     addNode(&bt1, 0);
     addNode(&bt1, 7);
     addNode(&bt1, 96);
     addNode(&bt1, 50);
     addNode(&bt1, 70);
     addNode(&bt1, 29);
     addNode(&bt1, 13);
     addNode(&bt1, 9);


     //la creation de la 2eme arbre
     addNode(&bt2, 11);
     addNode(&bt2, 60);
     addNode(&bt2, 8);
     addNode(&bt2, 11);
     addNode(&bt2, 26);
     addNode(&bt2, 100);
     addNode(&bt2, 40);
     addNode(&bt2, 66);
     addNode(&bt2, 95);
     addNode(&bt2, 58);
     addNode(&bt2, 66);
     
     
    /*struct nodee* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);*/
 
   
 



    /* //la creation de la 3eme arbre
     addNode(&bt3, 171);
     addNode(&bt3, 60);
     addNode(&bt3, 8);
     addNode(&bt3, 106);
     addNode(&bt3, 26);
     addNode(&bt3, 1);
     addNode(&bt3, 40);
     addNode(&bt3, 66);
     addNode(&bt3, 95);
     addNode(&bt3, 578);
     addNode(&bt2, 66);*/
     
     printf("---------------------------------contenu de mon arbre----------------------------\n");
     printf("\n");
     printf("---------------------Le contenu de L\'arbre bt1:------------------\n");
     printf("\n");
     printTree(bt1);
     puts("-----------------------------------------------------------------------");
     printf("---------------------Le contenu de L\'arbre bt2:-------------------\n");
     printf("\n");
     printTree(bt2);
    /*printf("---------------------Le contenu de L\'arbre bt3:-------------------\n");
     printf("\n");
     printTree(bt3);*/
     
     

     // le test de la qst 1
     printf("-------------------------question 01 recursive-------------------------\n");
     int result11 = equalBTreesRecu(bt1, bt2);
     if(result11>0){
          printf("\n \t Les deux arbres donnée sont egaux.\n");
          printf("\n");
     }else{
          printf("\n \t Les deux arbres sont distincts!\n");
          printf("\n");
     }
     
     printf("-------------------------question 01 iterative-------------------------\n");
     
     int result12 = isIdentical(bt1, bt2);
     if(result12>0){
          printf("\n \t Les deux donnée arbres sont egaux.\n");
          printf("\n");
     }else{
          printf("\n \t Les deux arbres donnée sont distincts!\n");
          printf("\n");
     }

     // le test de la qst 2
     printf("-------------------------question 02 recursive-------------------------\n");
     
     int result21 = isSubBTreeRecu(bt1, bt2);
     if(result21>0){
          printf("\n \t bt1 est un sous-arbre de bt2.\n");
          printf("\n");
           
     }else{
          printf("\n \t bt1 n\'est pas un sous-arbre de bt2!\n");
          printf("\n");
          
     }
  
     printf("-------------------------question 02 iterative-------------------------\n");

     int result22 = IssubBTreesIter(bt1, bt2);
     if(result22>0){
          printf("\n \t bt1 est un sous-arbre de bt2.\n");
           printf("\n");
     }else{
          printf("\n \t bt1 n\'est pas un sous-arbre de bt2!\n");
           printf("\n");
     }
    // ISsubBTreesIter(bt1, bt2);
printf("\n");




//----------------------------------------------------------------------------Verification 02-------------------------------------------------------------------------------------
printf("*********************************************************************************************************************\n \n \n");
       printf("--------------------------------------VERIFICATION 02 ----------------------------------------------------\n \n \n");

      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     // -----------------------------------le test de la qst 3 recursive
          printf("---------------------------------question 03 recursive----------------------------\n");
          printf("\n");
     int result3 = findElemRec(bt1, 100);
     if(result3>0){
          printf("\t 100 appartient a l\'arbre bt1!\n");
          printf("\n");
     }else{
          printf("\t 100 n\'appartient pas a l\'arbre bt1!\n");
          printf("\n");
     }
     //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     //-----------------------------------------Le test de la qst 3 iterative
           printf("---------------------------------question 03 iterative----------------------------\n");
           printf("\n");
     findElemIter(bt1,100);
     printf("\n");
     puts("--------------------------------------------------------------------------------------------");
   
     
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     //-------------------------------------------- le test de la qst 4 recursive
          printf("---------------------------------question 04 recursive----------------------------\n");
          printf("\n");
          sommet = findMinRec(bt1);
  
     printf("\t Le minimun de l'arbre : %d\n",sommet);
     printf("\n");
     //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      // -------------------------------------------le test de la qst 4 iterative
       printf("---------------------------------question 04 iterative----------------------------\n");
       printf("\n");
     findMinIter(bt1);
     printf("\n");
     puts("-------------------------------------------------------------------------------------------");

     

     //--------------------------------------le test qst5 iterative
     printf("------------------------------------question 05 iterative--------------------------------\n");
      printf("\n");
      printf(" parcours largeur :\n");
      printf("\n");
    // largeur(bt1);
     //--------------------------------------test qst5 recursive
     printf("---------------------------affichage en largeur version recursive------------------------------- \n");
       printLevelOrder(bt1);
     // vider l espace memoire occupe pour les 2 arbres
     clearTree(&bt1);
     clearTree(&bt2);
    


     

    
	return 0;
}
