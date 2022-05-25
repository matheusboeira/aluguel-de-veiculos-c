# Aluguel de Veículos em C

O presente projeto teve como objetivo a criação de um _software_ para gerencimento de uma locadora de veículos. Este, foi totalmente desenvolvido na linguagem C, visando compreender um novo paradigma de programação, a `programação procedural`. 

Este projeto não possui nenhum dado sensível e é totalmente fictício. Enfatizando que o presente projeto foi desenvolvido para fins de aprendizado. A versão não possui implementação gráfica. Para fins de visualização, partes do _software_ será exposta neste documento.

### Demonstração do _Software_

![preview](https://user-images.githubusercontent.com/76896958/170173865-8c3e2884-6dc7-4d6e-a963-b0481e182d4b.gif)

## Informações extras

Este projeto necessita de um compilador em C, juntamente com o utilitário Makefile para juntar todos os arquivos objetos e gerar um executável.

O recomendado, e utilizado neste projeto, é o [MSYS2](https://www.msys2.org/).

Desta forma, basta entrar na pasta `src` e digitar `make` que o programa será compilado e gerado um _.exe_ na pasta _out_.

```bash
> cd src
> make
```

Em caso de erros de compilação, será necessário limpar manualmente os arquivos `.o` gerados pelo `make`, fazendo desta forma: `make clean`. 

OBS.: O comando `make` só irá funcionar caso esteja dentro da pasta `src` do projeto e possua ele no ambiente de variáveis do ambiente.
