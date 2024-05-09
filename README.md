# LightsOut RGB

<p>
 O LightsOut RGB consiste em uma versão modificada do LightsOut, um jogo físico em que há uma matriz de luzes que podem estar ligadas ou desligadas (ON/OFF). Diante disso, o objetivo do jogo consiste em desligar todas as luzes, considerando que, ao clicar em determinado botão, o estado de sua luz e o estado das luzes adjacentes são invertidos. 
</p>
 Em contra partida, essa nova versão possui 4 estados possíveis (RED, GREEN, BLUE, OFF) abreviados, respectivamente, como (R, G, B, W). Somado a isso, a inversão de estado ocorre em todas as luzes vertical e horizontalmente ao botão clicado, com excessão de determinados botões "quebrados" que possuem comportamento específico. 
<p>

<p>
 Diante do exposto, o objetivo desse projeto consiste em criar um programa capaz de atender as seguintes demandas. São elas: 
</p>

<ol>
<li>ler a especificação do desafio (Input)</li>
<li>Gerar um modelo PDDL do jogo LightsOut RGB</li>
<li>Chamar um planejador</li>
<li>Obter o plano do planejador</li>
<li>Gerar a saída no formato especificado (Output)</li>
</ol>

<p>
 A seguir, confira as especificações de entrada e saída, bem como as característica de cada tipo de botão.
</p>

# Input

# Output

# Botões 


 ID | Defeito | Mudança de Estado
----| ------- | -----------------
1   | Não há mudança de estado quando clicado | click em mesma linha ou coluna
2   | Não há mudança de estado decorrente de click em mesma coluna | quando clicado ou click em mesma linha
3   | Não há mudança de estado decorrente de click em mesma linha | quando clicado ou click em mesma coluna
4   | Não há mudança de estado decorrente de click em mesma linha e coluna | quando clicado
5   | Nenhum | quando clicado ou click em mesma linha ou coluna

<i>Resumo (Mudança de Estados):</i>

 ID |       Defeito      |    quando clicado  | click em mesma linha | click em mesma coluna |
----| ------------------ | ------------------ | -------------------- | --------------------- |
1   | :white_check_mark: |        :x:         |  :white_check_mark:  |  :white_check_mark:   |
2   | :white_check_mark: |        :x:         |  :white_check_mark:  |          :x:          |
3   | :white_check_mark: |        :x:         |         :x:          |  :white_check_mark:   |
4   | :white_check_mark: | :white_check_mark: |         :x:          |          :x:          |
5   |        :x:         | :white_check_mark: |  :white_check_mark:  |  :white_check_mark:   |

# Tabela de comandos

Comando   | Função
--------- | ------
sudo apt-get install gcc | instalação do compilador .c
sudo apt-get install g++ | instalação do compilador .cc
gcc [file_name.c] -o[executable_name] | cria um executável a partir de um file.c
g++ [file_name.cc] -o[executable_name] | cria um executável a partir de um file.cc

# Referências

