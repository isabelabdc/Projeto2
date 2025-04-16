# Projeto2
Projeto 2 -- Desenvolvimento de algoritmos

GRUPO:
Isabela Bonoto de Castro - 24.224.008-3
Gustavo Runge Passarelli - 52.224.004-3

OBJETIVO:
Este projeto tem como objetivo simular uma exchange de criptomoedas via console, permitindo que usuários realizem operações como depósito, saque, compra e venda de
criptomoedas. Cada usuário possui uma carteira individual com saldo em reais, bitcoin, ethereum e ripple, além de um histórico das últimas 100 transações realizadas.
Para garantir que os dados sejam salvos, as informações dos usuários e seus extratos são armazenadas em arquivos binários. As cotações das criptomoedas são atualizadas
aleatoriamente dentro de uma variação de -5% a 5%, simulando a oscilação constante do mercado.

FORMA DE USO DO PROGRAMA:
Ao iniciar o programa, o usuário deve escolher entre fazer login ou realizar um novo cadastro informando seu CPF, nome e senha. Após realizar o login com o CPF e senha
corretos, o menu principal será exibido com as opções de consultar saldo ou extrato, depositar ou sacar reais da carteira, comprar ou vender criptomoedas, atualizar as
cotações e sair. As operações são feitas digitando os dados solicitados, como valores e confirmação de senha. Ao sair, todas as informações são salvas em arquivos para
que estejam disponíveis na próxima execução do programa.

FORMA DE COMPILAÇÃO E EXECUÇÃO:
Para compilar e executar o código no Windows, foi feito o download do MinGW-w64, que permite compilar programas em C usando o GCC.

Após fazer o download e devidas configurações, abra o prompt de comando ou terminal no diretório do projeto e digite o seguinte comando, para compilar os dois arquivos ".c" juntos:

"gcc main.c projeto.c -o exchange"

Esse comando irá gerar um arquivo executável chamado "exchange.exe", para executá-lo, digite no terminal:

"exchange.exe"

A exchange será iniciada e estará pronta para uso.

No Linux, após compilar com o mesmo comando, execute o programa com:
"./exchange"
