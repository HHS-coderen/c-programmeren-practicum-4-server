# C Practicum – Les 4: Socket Server (WinSock)

Semester NSE 4 | Alle code is geschreven in 100% C

## Beschrijving

Deze map bevat de servercode behorende bij les 4 van het C practicum. In deze les wordt kennisgemaakt met netwerkcommunicatie via sockets in C, gebruikmakend van de WinSock API op Windows.

---

## Behandelde onderdelen

### Opgave 1 – Lokale socket server & client

- Opzetten van een eenvoudige **WinSock socket server** die reageert op verzoeken van een client.
- Bijbehorende **client applicatie** schrijven en testen op dezelfde machine.
- Aantonen dat met **blocking `recv`** meerdere clients bediend kunnen worden door één server — zonder multithreading.
- Communicatie via **key-value berichten** (in plaats van vrije tekst), bijvoorbeeld het doorgeven van temperatuur of luchtvochtigheid, met als antwoord een ventilatorsnelheid.
- Optioneel: werken met **JSON** via de [cJSON bibliotheek](https://github.com/DaveGamble/cJSON) (`cJSON.h` + `cJSON.c` toevoegen aan het project).

### Opgave 2 – Communicatie tussen meerdere machines

- Server draaien op de eigen machine en een **client op een andere machine** een request laten sturen.
- Onderzoeken wat er nodig is op zowel de server- als de clientmachine.
- Testen met **telnet of curl** vanuit Linux om een request naar de server te sturen en de verstuurde data te inspecteren.
- Vanuit een eigen C-programma een **HTTP 1.1 request** sturen naar een webserver op het internet en de response analyseren (statuscodes, headers, body).

---

## Referenties

- [cJSON – JSON library voor C](https://github.com/DaveGamble/cJSON)
- [HTTP/1.1 protocol uitleg – MDN](https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview)
