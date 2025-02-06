# Sistema de Caixas e Filas de Supermercado
Trabalho de complementação de Programação de Computadores 1.
Programa desenvolvido em linguagem C.

Para executar em ambiente Windows abra a pasta src no terminal e coloque no comando de execução os 3 arquivos com final ".c" da pasta.

Exemplo: gcc -o run main.c cliente.c fila.c
./run

Possui um arquivo Makefile para execução em ambiente Linux ou WSL.

Ao baixar a pasta do repositório, abra a pasta no terminal e execute o arquivo Makefile.
Basta digitar no terminal: make clean && make && make run.

Esse sistema simula um controle de clientes e caixas de um supermercado.
É possível inserir novos clientes por prioridade de atendimento, fazer o atendimento dos clientes, abrir e fechar os caixas e ter informações de todos os clientes que ainda estão nas filas do mercado.
