# O Problema de Fanneuil-Hall

## Grupo

Gabriel Militao Vinhas Lopes RA: 135801
João Guilherme Fidelis RA: 136242
Pedro Emilio Machado de Brito RA: 137264
O problema foi originalmente escrito por Grant Hutchins.

## Problema

Temos três tipos de thread: imigrantes, espectadores, e um juíz. Imigrantes devem esperar, fazer um check in, e sentar. Em algum ponto, o juíz entra no recinto. Quando o juíz está la dentro, ninguém mais pode entrar e os imigrantes não pode sair. Espectadores podem sair. Assim que todos os imigrantes fizerem check in, o juíz pode confirmar suas naturalizações. Depois de confirmado, os imigrantes pegam seus certificados. O juíz pode sair em algum ponto após a confirmação. Agora, espectadores podem entrar novamente. Depois de pegarem seus certificados, o imigrantes podem sair.

Então facilitando a visualização do problema, aqui está o que cada thread deve fazer:
- Imigrantes - devem invocar enter, checkIn, sit, swear, getCertificate e leave.
- O juíz invoca enter, confirm e leave.
- Espectadores devem invocar enter, spectate e leave.
- Enquanto o juíz está no recinto, ninguém pode entrar e os imigrantes não podem sair.
- O juíz não pode invocar confirm enquanto todos os imigrantes que invocaram enter não invocarem checkIn.
- Os imigrantes não podem pegar seus certificados enquanto o juíz tiver invocado confirm.

Em nosso problema, implementamos a solução extendida. Ela evita que outro juíz consiga entrar no recinto enquanto imigrantes que ja pegaram seu certificado estiverem dentro, pois isso faria que estes imigrantes ficassem parados vendo outra cerimônia até poder sair.

## Instruções de uso

Ao compilar com make, digite ./projeto .
Conforme solicitado, digite o número de espectadores (no máximo 5 para caber na tela) e de imigrantes (no máximo 4) que você deseja ver participando.
Parar com ctrl+c.
