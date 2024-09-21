# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Diretórios
SRCDIR = src
INCDIR = include
BINDIR = bin

# Arquivos fonte e objeto
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)
TARGET = $(BINDIR)/projeto

# Regra padrão
all: $(TARGET)

# Regra para criar o diretório bin

$(BINDIR):
	@mkdir -p $(BINDIR)

# Regra para compilar o projeto
$(TARGET): $(BINDIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar arquivos objeto
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar arquivos compilados
clean:
	rm -rf $(BINDIR)

# Regra para executar o projeto
run: $(TARGET)
	./$(TARGET)