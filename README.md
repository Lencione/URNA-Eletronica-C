# PROJETO URNA ELETRÔNICA - AULA AOC

### Descrição
Desenvolver em C um projeto de urna eletrônica, desenhando LAYOUT sem usar a biblioteca graphics.h
O sistema não permite que o mesmo usuário vote duas vezes, sendo necessário inserir seu RA para votar.
Colher os votos por ilimitadas vezes, até que o programa seja solicitado para encerrar.
Mostrar os votos de cada candidato antes de finalizar o programa.

### Bibliotecas usadas
**<stdio.h>** - Entrada e saída padrão da linguagem<br>
**<windows.h>** - Manipulação e informações do windows<br>
**<conio.h>** - Entrada e saída além de funções com o windows<br>
**<string.h>** - Manipulação de strings<br>
**<mmsystem.h>** - Manipulação de áudio<br>

### O que torna o sistema diferente?
O programa foi todo projetado para funcionar com a maior semelhança possível de uma urna eletrônica verdadeira.
Existe uma função para manipulação e tradução das coordenadas do ponteiro do mouse para funcionar na tela.
Os botões foram todos mapeados manualmente através de calculos em torno da tela.
Não há interação alguma com o teclado, a não ser o último comando para finalizar o programa (esperar o 's' para finalizar)
Reaproveitamento de funções em todo o projeto.
**Clean Code**, separado por funções, de fácil leitura.
Uso de sons em formato WAV para deixar o sistema mais didático.

 
![gif-do-garoto-menino-dando-joinha](https://user-images.githubusercontent.com/44005188/194983145-dab6bef7-ba1e-4237-b663-afef7042d98e.gif)
