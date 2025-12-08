# 🌀 CartoLang

**CartoLang** is a **cartoon-inspired programming language** modeled after **C++**, where every keyword and structure is themed around iconic animated characters and worlds.  

Code with **fun**, **creativity**, and **laughter** — bring your favorite cartoons to life through syntax that blends **logic** and **animation magic**!  

---
# ✨ Introduction

We all have wonderful childhood memories of watching cartoons — how we loved them, followed every episode, and even tried to imitate our favorite characters. Those memories are still stuck in our minds, full of joy and imagination.

That’s where the idea of CartoLang came from — a programming language that lets you write code using your favorite cartoon characters and their iconic actions.

Each keyword in the language is inspired by a famous cartoon character or a move they do, making coding not only fun but also full of creativity.

---
### 🌟 Featured Cartoon Characters  
🐭 **Mickey Mouse** | 🐼 **Po (Kung Fu Panda)** | 🧽 **SpongeBob** | 🐧 **Penguins of Madagascar** | 🦇 **Batman** | 🦸 **Superman** | 🧀 **Jerry** | 🐱 **Tom** | 🤥 **Pinocchio** |  **Buzz Yeteer 🚀**

---
## 📁 Project Structure
```
CartoLang/
│
├── build/                          # Compiled executables
│   ├── lexer.exe                   # Phase 1: Lexical Analyzer
│   └── parser.exe                  # Phase 2: Parser with Semantic Analysis
│
├── src/                            # Source code
│   ├── phase-1-lexical_analysis/   # Phase 1: Lexical Analysis
│   │   ├── build.bat               # Build script for lexer
│   │   ├── lexer.cpp               # Lexer implementation
│   │   ├── lexer.h                 # Lexer header
│   │   ├── main.cpp                # Main entry point for lexer
│   │   ├── token.cpp               # Token class implementation
│   │   └── token.h                 # Token class header
│   │
│   └── phase-2-syntax_analysis/    # Phase 2: Syntax & Semantic Analysis
│       ├── build.bat               # Build script for parser
│       ├── Grammar.txt             # Language grammar specification
│       ├── main.cpp                # Main entry point for parser
│       ├── parser.cpp              # Parser implementation with semantic checks
│       └── parser.h                # Parser header with AST and symbol table
│
├── tests/                          # Test files
│   ├── lexer_test_1.cl             # Test case 1 for lexer
│   └── lexer_test_2.cl             # Test case 2 for lexer
│
└── README.md                       # Project documentation
```

---

## 📚 Language Features

### Data Types (Keywords)
- `bat_num` → `int` (Batman's number)
- `super_num` → `float` (Superman's floating power)
- `Jerry_hide` → `string` (Jerry hiding in text)
- `tom_char` → `char` (Tom's single character)
- `pinocchio` → `bool` (Pinocchio's truth/lie)

### Control Flow
- `sponge_bob_check` → `if` statement
- `sponge_bob_try_again` → `else` statement
- `penguins_madagascar_repeat` → `while` loop
- `penguins_madagascar_iteration` → `for` loop

### Functions
- `po_kungfu` → function declaration (Po's Kung Fu )
- `po_kungfu_mastered` → `return` statement

### I/O Operations
- `buzz_speak` → `print/cout` (Buzz speaking)
- `buzz_receive` → `input/cin` (Buzz receiving)

---

## 📝 Example Code
```cartolang
po_kungfu sayHello(){
    buzz_speak("Hello World!");
}

bat_num age = 25;
Jerry_hide name = "Zeyad";
pinocchio isTrue = 0;

sponge_bob_check(age > 18){
    buzz_speak("Adult");
} sponge_bob_try_again {
    buzz_speak("Minor");
}
```

---
### Installation

1. **Clone the repository:**
```bash
   git clone https://github.com/ZeyadGasser/CartoLang.git
   cd CartoLang
```

2. **Build Phase 1 (Lexical Analyzer):**
```bash
   cd src/phase-1-lexical_analysis
   build.bat          
```

3. **Build Phase 2 (Parser with Semantic Analysis):**
```bash
   cd ../phase-2-syntax_analysis
   build.bat         
```

## 👨‍💻 Author

**Zeyad Gasser** - *Creator of CartoLang*

---

## 🎉 Have Fun Coding with Cartoons!

Relive your childhood memories while learning programming — because code should be **fun**, **creative**, and full of **cartoon magic**! 🌟🎨
