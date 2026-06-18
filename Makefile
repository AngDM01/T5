CONTAINER = ServApp_Sitio_Tarjetas
IMAGE = apache-cgi
URL = http://localhost/

APP_DIR = app

SRC_DIR = $(APP_DIR)/src
CGI_DIR = $(APP_DIR)/cgi
INCLUDE_DIR = $(APP_DIR)/include

BUILD_DIR = $(APP_DIR)/build
BIN_DIR = $(APP_DIR)/bin

# =========================

# FUENTES

# =========================

CGI_FILES = $(wildcard $(CGI_DIR)/*.cpp)

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

CGI_OBJECTS = $(patsubst $(CGI_DIR)/%.cpp,$(BUILD_DIR)/cgi_%.o,$(CGI_FILES))
CGI_TARGETS = $(patsubst $(CGI_DIR)/%.cpp,$(BIN_DIR)/%.cgi,$(CGI_FILES))

# =========================

# BUILD CGI

# =========================

all: $(CGI_TARGETS)

$(BUILD_DIR)/%.o:
	docker exec $(CONTAINER) mkdir -p app/build
	docker exec $(CONTAINER) g++ -Wall -std=c++17 -Iapp/include -c app/src/$*.cpp -o app/build/$*.o

$(BUILD_DIR)/cgi_%.o:
	docker exec $(CONTAINER) mkdir -p app/build
	docker exec $(CONTAINER) g++ -Wall -std=c++17 -Iapp/include -c app/cgi/$*.cpp -o app/build/cgi_$*.o

$(BIN_DIR)/%.cgi: $(BUILD_DIR)/cgi_%.o $(SRC_OBJECTS)
	docker exec $(CONTAINER) mkdir -p app/bin
	docker exec $(CONTAINER) g++ app/build/cgi_$*.o $(SRC_OBJECTS) -o app/bin/$*.cgi
	docker exec $(CONTAINER) chmod +x app/bin/$*.cgi

@$(MAKE) url

# =========================

# DOCKER

# =========================

image:
	docker build -t $(IMAGE) .

up:
	@docker start $(CONTAINER) 2>NUL || docker run -d \
		--name $(CONTAINER) \
		-p 80:80 \
		-v "$(CURDIR)/app:/usr/local/apache2/app" \
		$(IMAGE)

	@$(MAKE) url

start:
	docker start $(CONTAINER)

	@$(MAKE) url
	
stop:
	docker stop $(CONTAINER)

restart:
	docker restart $(CONTAINER)

logs:
	docker logs -f $(CONTAINER)

shell:
	docker exec -it $(CONTAINER) bash

# =========================

# LIMPIEZA

# =========================

clean:
	docker exec $(CONTAINER) sh -c 'rm -rf app/build/* app/bin/*'

remove-container:
	docker rm -f $(CONTAINER)

remove-image:
	docker rmi -f $(IMAGE)

destroy: remove-container remove-image

rebuild: clean all

dev: image up all

url:
	@echo Servidor iniciado:
	@echo.
	@echo    $(URL)
	@echo.