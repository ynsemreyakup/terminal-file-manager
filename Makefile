# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Iinclude -Wall -g

# Dizinler
SRCDIR = src
BINDIR = bin
INCDIR = include
LOGDIR = logs
BUILDDIR = build

# Kaynak dosyaları ve hedef dosyalar
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))
TARGET = $(BINDIR)/file_manager
LOGFILE = $(LOGDIR)/operations_log.txt  # Log dosyasının tam yolu

# Varsayılan hedef
all: $(TARGET)

# Çalıştırılabilir dosya oluşturma
$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Kaynak dosyaları derleme
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Temizlik işlemi
clean:
	rm -f $(BUILDDIR)/*.o
	rm -f $(BINDIR)/*
	rm -f $(LOGDIR)/*

# Log dosyasını temizleme (isteğe bağlı)
clean_logs:
	rm -f $(LOGFILE)
