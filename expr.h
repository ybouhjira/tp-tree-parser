#ifndef EXPR_H
#define EXPR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>


#define est_op(c) (c == '-' || c == '+' || c == '*' || c == '/')

#define digit_to_int(d) (d - '0')

/**
 * Type de données stocké dans les noeud de l'arbre
 */
typedef union
{
  float nbr; // Une nombre réel (ex : -1.23)
  char op; // un opérateur (ex : +)
} Valeur;

/** Indique le type stocker dans un noeud de l'arbre
 * Float pour un nombre et char pour un opérateur
 */
typedef enum {FLOAT, CHAR} TypeValeur;

/**
 *  Structure de l'arbre
 */
typedef struct Arbre
{

  Valeur val;
  TypeValeur type;
  struct Arbre *g, *d;
} Arbre;


Arbre *lire_op(char* expr, int *pos)
{
  assert(est_op(expr[*pos]));
  Arbre *noeud = calloc(1, sizeof(Arbre));
  noeud->val.op = expr[*pos];
  noeud->type = CHAR;
  (*pos)++;
  return noeud;
}

Arbre *lire_nbr(char *expr, int *pos)
{
  int signe = 1; // signe 1 positif et -1 négatif
  float nbr = 0; // Le nombre à lire


  // opérateur unaire + ou -
  if(expr[*pos] == '-' || expr[*pos] == '+')
      signe = expr[(*pos)++] == '-' ? -1 : 1 ;

  // partie entière
  while(isdigit(expr[*pos]))
      nbr = nbr * 10 + digit_to_int(expr[(*pos)++]);

  // partie décimale
  if(expr[*pos] == '.')
    {
      int i = 1;
      (*pos)++;
      while(isdigit(expr[*pos]))
        {
          nbr += digit_to_int(expr[*pos]) * pow(10, -i);
          (*pos)++;
          i++;
        }
    }

  Arbre *arb = calloc(1, sizeof(Arbre));
  arb->val.nbr = nbr * signe;
  arb->type = FLOAT;
  return arb;
}

Arbre *lire_expr(char *expr, int *pos)
{
  // TODO
  if(expr[*pos] == '(') // sous expression ex : (1 + 2 - 3)
    {
      return NULL;
    }
  else // nombre ex : 1.2
    {
      return lire_nbr(expr, pos);
    }

  return NULL;
}


#endif // EXPR_H
