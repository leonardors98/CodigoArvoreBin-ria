#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoEndereco
{
	int cep;
	char numero[10];
	char cidade[30];
	char logradouro[50];
	char bairro[50];
	char estado[50];
	char pais[30];

} TEndereco;

typedef struct tipoPessoa
{
	char nome[50];
	char email[50];
	int cpf;
	int celular;
	TEndereco endereco;
} TPessoa;

typedef struct tipoNo
{
	TPessoa pessoa;
	struct tipoNo *esq, *dir;
} TNo;

void apresentarEndereco(TPessoa *Pessoa)
{
	printf("\n Cep: %d", Pessoa->endereco.cep);
	printf("\n Numero: %s", Pessoa->endereco.numero);
	printf("\n Cidade: %s", Pessoa->endereco.cidade);
	printf("\n Logradouro: %s", Pessoa->endereco.logradouro);
	printf("\n Bairro: %s", Pessoa->endereco.bairro);
	printf("\n Estado: %s", Pessoa->endereco.estado);
	printf("\n Pais: %s", Pessoa->endereco.estado);
}

void apresentarPessoa(TNo *Tno)
{
	printf("\n\n Nome: %s", Tno->pessoa.nome);
	printf("\n Cpf: %i", Tno->pessoa.cpf);
	printf("\n Email: %s", Tno->pessoa.email);
	printf("\n Celular: %i", Tno->pessoa.celular);
	apresentarEndereco(&Tno->pessoa);
}

TNo *inserir(TNo *raiz, TPessoa *Pessoa)
{
	if (raiz == NULL)
	{
		raiz = new TNo;
		raiz->pessoa = *Pessoa;
		raiz->esq = NULL;
		raiz->dir = NULL;
	}
	else
	{
		if (Pessoa->cpf < raiz->pessoa.cpf)
		{
			raiz->esq = inserir(raiz->esq, Pessoa);
		}
		else
		{
			raiz->dir = inserir(raiz->dir, Pessoa);
		}
	}
	return raiz;
}

void lerDadosEndereco(TPessoa *elemento)
{
	printf("\n Informe seu cep: ");
	scanf("%i", &elemento->endereco.cep);
	printf("\n Informe o Numero da Casa:");
	fflush(stdin);
	gets(elemento->endereco.numero);
	printf("\n Informe sua cidade : ");
	fflush(stdin);
	gets(elemento->endereco.cidade);
	printf("\n Informe seu Logradouro: ");
	fflush(stdin);
	gets(elemento->endereco.logradouro);
	printf("\n Informe seu Bairro: ");
	fflush(stdin);
	gets(elemento->endereco.bairro);
	printf("\n Informeu seu Estado: ");
	fflush(stdin);
	gets(elemento->endereco.estado);
	printf("\n Informe seu Pais: ");
	fflush(stdin);
	gets(elemento->endereco.pais);
}

void lerDadosPessoa(TPessoa *elemento)
{
	printf("\n Informe seu cpf: ");
	scanf("%i", &elemento->cpf);
	printf("\n Informe seu nome: ");
	fflush(stdin);
	gets(elemento->nome);
	printf("\n Informe seu email: ");
	fflush(stdin);
	gets(elemento->email);
	printf("\n Informe seu celular: ");
	scanf("%i", &elemento->celular);
	printf("\n\n Informe dados do endereco: ");
	lerDadosEndereco(elemento);
}

void preOrdem(TNo *raiz)
{
	if (raiz != NULL)
	{
		apresentarPessoa(raiz);
		preOrdem(raiz->esq);
		preOrdem(raiz->dir);
	}
}

TNo *consultarCpf(TNo *auxRaiz, int auxValor)
{
	if (auxRaiz == NULL)
	{
		printf("\n Usuario nao encontrado!");
		return 0;
	}
	else
	{
		if (auxRaiz->pessoa.cpf == auxValor)
		{
			printf("\n Cpf Encontrado!");
			return auxRaiz;
		}
		else
		{
			if (auxValor < auxRaiz->pessoa.cpf)
			{
				return consultarCpf(auxRaiz->esq, auxValor);
			}
			else
			{
				return consultarCpf(auxRaiz->dir, auxValor);
			}
		}
	}
}

int sobeMaiorDireita(TNo *aux)
{
	while (aux->dir != NULL)
	{
		aux = aux->dir;
	}
	return (aux->pessoa.cpf);
}

TNo *remover(TNo *raiz, int auxValor)
{
	if (raiz == NULL)
	{
		printf("\n Cpf nao encontrado!");
	}
	else
	{
		if (auxValor < raiz->pessoa.cpf)
		{
			raiz->esq = remover(raiz->esq, auxValor);
		}
		else
		{
			if (auxValor > raiz->pessoa.cpf)
			{
				raiz->dir = remover(raiz->dir, auxValor);
			}
			else //encontrei o valor
			{
				//se o elemento nao tiver sub-arvore direita			
				if (raiz->dir == NULL)
				{
					TNo *aux;
					aux = raiz;
					raiz = raiz->esq;
					free(aux);
				}
				else
				{
					if (raiz->esq == NULL)
					{
						TNo *aux;
						aux = raiz;
						raiz = raiz->dir;
						free(aux);
					}
					else //possui 2 sub-arvores
					{
						//raiz->pessoa.cpf = sobeMaiorDireita(raiz->esq);
						raiz->esq = remover(raiz->esq, sobeMaiorDireita(raiz->esq));
					}
				}
			}
		}
		printf("\n Pessoa excluida com sucesso! ");
	}
	return raiz;
}

void modificarDadosConta(TNo *auxRaiz, int auxValor)
{
	TNo *temp = consultarCpf(auxRaiz, auxValor);

	lerDadosPessoa(&temp->pessoa);
}

int main()
{
	TNo *raiz;
	raiz = NULL; 

	TPessoa elemento;
	TEndereco endereco;

	int opcao;

	do
	{
		printf("\n\n 1 - Inserir Novo usuario");
		printf("\n 2 - Apresentar pre-ordem");
		printf("\n 3 - Consultar valor - recursivo");
		printf("\n 4 - Excluir valor da arvore");
		printf("\n 5 - Alterar valor da arvore");
		printf("\n 0 - Sair");
		printf("\n Escolha uma opcao: ");
		scanf("%d", &opcao);
		system("cls");
		switch (opcao)
		{
		case 1:
		{
			lerDadosPessoa(&elemento);
			raiz = inserir(raiz, &elemento);
			break;
		}

		case 2:
		{
			if (raiz == NULL)
			{
				printf("\n Arvore vazia! \n");
			}
			else
			{
				preOrdem(raiz);
				break;
			}
		}

		case 3:
		{
			int auxValor;
			TPessoa encontrou;
			printf("\n Informe CPF a ser consultado: ");
			scanf("%d", &auxValor);
			raiz = consultarCpf(raiz, auxValor);

			break;
		}
		case 4:
		{
			int auxValor;
			printf("\n Informe CPF para exclusao da conta");
			scanf("%d", &auxValor);
			raiz = remover(raiz, auxValor);
			break;
		}
		case 5:
		{
			int auxValor;
			printf("\n Informe CPF para modificar a conta");
			scanf("%d", &auxValor);
			modificarDadosConta(raiz, auxValor);
			break;
		}
		}

	} while (opcao != 0);
}
