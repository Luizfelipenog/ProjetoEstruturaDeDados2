
# Trabalho ED2 - Sistema de Árvore

## Descrição

Este repositório contém o trabalho de Estruturas de Dados 2 (ED2), desenvolvido em C. O sistema implementa uma estrutura de árvore 2-3, com funcionalidades para gerenciar informações sobre álbuns, artistas e músicas.

### Estrutura

O código está dividido em diferentes arquivos responsáveis por:
- **Álbum**: Contém informações sobre um álbum musical, incluindo o título e o ano de lançamento.
- **Artista**: Contém informações sobre os artistas, como nome e suas músicas.
- **Música**: Cada música está associada a um álbum e um artista.
  
## 📁 Estrutura do Projeto

```
TrabalhoEd2/
├── 📁 TrabalhoEd2/
│   ├── 📄 album.c  # Código-fonte para a implementação do álbum
│   ├── 📄 album.h  # Cabeçalho do álbum
│   ├── 📄 artista.c  # Código-fonte para a implementação do artista
│   ├── 📄 artista.h  # Cabeçalho do artista
│   ├── 📄 main.c  # Código principal do projeto
│   ├── 📄 musica.c  # Código-fonte para a implementação da música
│   ├── 📄 musica.h  # Cabeçalho da música
│   └── 📁 output/
│       ├── 📄 album.exe  # Executável do programa do álbum
│       └── 📄 main.exe  # Executável principal
├── 📁 trabalho 2 arvore 2-3/
│   ├── 📄 album.c  # Implementação de árvore 2-3 para o álbum
│   ├── 📄 album.h  # Cabeçalho da árvore 2-3 para o álbum
│   ├── 📄 artista.c  # Implementação de árvore 2-3 para o artista
│   ├── 📄 artista.h  # Cabeçalho da árvore 2-3 para o artista
│   ├── 📄 main.c  # Implementação principal do sistema de árvore 2-3
│   └── 📁 output/
│       └── 📄 main.exe  # Executável do programa com árvore 2-3
└── .git/  # Histórico do Git e arquivos de controle de versão
```

## 📌 Requisitos

Para compilar e executar o código, você precisa ter:
- **GCC** (compilador C) instalado.
- **Terminal ou Prompt de Comando**.

No Linux, você pode instalar o GCC com:

```bash
sudo apt update
sudo apt install build-essential
```

## ▶️ Como Rodar

### 1. Clone o repositório

```bash
git clone https://github.com/usuario/TrabalhoEd2.git
cd TrabalhoEd2
```

### 2. Compile os arquivos

Para compilar os arquivos de código:

```bash
gcc album.c artista.c musica.c main.c -o main.exe
```

### 3. Execute o programa

```bash
./main.exe
```

## 📝 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).

## 📜 Contribuições

Se você deseja contribuir para este projeto, faça um fork, crie uma branch para suas alterações e envie um pull request.

