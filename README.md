# 🐍 Jogo da Cobrinha em C (Snake Game)

Um jogo clássico da Cobrinha desenvolvido em **C moderno** com renderização direta no terminal do Windows, suporte a níveis de dificuldade, placar de pontuação e recorde persistente.

🔗 **Repositório GitHub**: [https://github.com/vicenzocrlo/jogo_snake_C](https://github.com/vicenzocrlo/jogo_snake_C)

---

## 🚀 Funcionalidades

- **Menu Interativo**: Seleção de dificuldade (Fácil, Médio, Difícil).
- **Controles Responsivos**: Suporte a teclas `W`, `A`, `S`, `D` e **Setas do Teclado**.
- **Sistema de Frutas Especiais**: Frutas bônus (`$`) aparecem periodicamente concedendo mais pontos.
- **Painel de HUD**: Exibe Pontuação atual, Recorde (High Score), Frutas coletadas e Estado do jogo.
- **Pausa & Reinício**: Opção de pausar o jogo (`P`) e jogar novamente ao perder.
- **Efeitos de Áudio**: Sons simples via API do Windows ao coletar alimentos.

---

## 🎮 Controles

| Ação | Teclas |
| :--- | :--- |
| **Mover para Cima** | `W` ou `Seta para Cima` |
| **Mover para Baixo** | `S` ou `Seta para Baixo` |
| **Mover para Esquerda** | `A` ou `Seta para Esquerda` |
| **Mover para Direita** | `D` ou `Seta para Direita` |
| **Pausar / Despausar** | `P` |
| **Sair do Jogo** | `Q` ou `ESC` |

---

## 🛠️ Como Compilar e Executar

### Pré-requisitos
- Compilador C instalado (ex: **GCC / MinGW**, **Clang** ou **MSVC**).

### Compilação Rápida (Windows Script)
Basta dar um duplo clique no arquivo `build.bat` ou rodar no terminal:

```cmd
build.bat
```

### Compilação Manual via GCC
```cmd
gcc -O2 -Wall main.c game.c -o snake.exe
```

### Executar o Jogo
```cmd
snake.exe
```

---

## 📁 Estrutura do Projeto

```
c-snake-game/
├── main.c        # Ponto de entrada e loop principal do programa
├── game.c        # Lógica do jogo (movimento, colisões, renderização, entrada)
├── game.h        # Cabeçalho com definições de estruturas, constantes e protótipos
├── build.bat     # Script automatizado de compilação para Windows
├── .gitignore    # Regras para ignorar binários e arquivos temporários
└── README.md     # Documentação do projeto
```

---

## 📄 Licença

Este projeto é livre para uso e modificações. Desenvolvido em C para fins de estudo e entretenimento.
