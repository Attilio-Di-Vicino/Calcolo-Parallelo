# Laboratorio 13: Scheduling e for

## Osservazioni
- Il costrutto FOR divide automaticamente le iterazioni di un ciclo for tra i thread.
- A seconda del programma, la modalità di scheduling predefinita (modalità STATIC) potrebbe non essere ottimale.

- Per i cicli FOR in cui ogni iterazione richiede approssimativamente lo stesso tempo, la modalità STATIC funziona meglio poiché presenta un sovraccarico minimo.
- Per i cicli FOR in cui le iterazioni possono richiedere quantità di tempo diverse, la modalità DYNAMIC funziona meglio, in quanto il lavoro viene suddiviso in modo più uniforme tra i thread. Tuttavia, potrebbe esserci un ritardo dovuto alla riassegnazione del lavoro.
- È possibile specificare il parametro CHUNK o utilizzare la modalità GUIDED per ottenere un compromesso tra le due modalità descritte sopra.

È importante sottolineare che la scelta della modalità di scheduling migliore dipende dal problema specifico e dalla strategia parallela da implementare.