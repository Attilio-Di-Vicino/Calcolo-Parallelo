# Calcolo Parallelo - Parte Laboratorio

Questo repository è stato creato appositamente per supportare il corso di Calcolo Parallelo - Parte Laboratorio nell'ambito dell'esame di Informatica presso l'Università di Napoli "Parthenope". La libreria OpenMP viene utilizzata per l'implementazione dei programmi paralleli presenti nella repository.

## Come iniziare

È semplice come un **git clone**! Basta digitare il seguente comando nel tuo terminale preferito:

```shell
git clone https://github.com/Attilio-Di-Vicino/Calcolo-Parallelo.git
```

## Contenuto della repository

La repository contiene diversi nuclei computazionali implementati utilizzando OpenMP. I nuclei computazionali inclusi sono i seguenti:

- **Somma N numeri:** Implementazione parallela della somma di N numeri.
- **Somma di due vettori di lunghezza N:** Implementazione parallela della somma di due vettori di lunghezza N.
- **Prodotto scalare tra due vettori:** Implementazione parallela del prodotto scalare tra due vettori.
- **Matrice x vettore:** Implementazione parallela del prodotto tra una matrice e un vettore utilizzando due strategie di collezione dei dati: strategia 1 e strategia 2.
- **Decomposizione a blocchi della matrice:** Implementazione parallela della decomposizione a blocchi di una matrice utilizzando tre strategie: strategia 1 blocchi riga, strategia 2 blocchi colonna e strategia 3 blocchi riga colonna.
- **SAXPY:** Implementazione parallela del problema "SAXPY", un comune problema matematico che può essere parallelizzato e che viene utilizzato in vari campi.
- **Esercitazioni:** Varie esercitazioni sul calcolo parallelo.

## Utilizzo di OpenMP

Tutti i programmi presenti nella repository sfruttano le potenzialità offerte dalla libreria OpenMP per la programmazione parallela. OpenMP fornisce direttive ad alto livello come `#pragma omp parallel for`, ` #pragma omp parallel sections`, ecc., che semplificano l'implementazione del parallelismo. Inoltre, in alcuni casi, viene utilizzato esclusivamenta la direttiva `#pragma omp parallel` per gestire manualmente la distribuzione del lavoro ai thread generati dopo la fork-join.

## Contribuire

Se desideri contribuire a questo progetto, puoi clonare la repository, apportare le modifiche desiderate e inviare una pull request. Sarà valutata e integrata se ritenuta appropriata.
erimento per gli studenti che desiderano esplorare il mondo dell'informatica parallela e scoprire le meraviglie del calcolo distribuito.
