CONTAINER = ServApp_Sitio_Tarjetas
CONTAINER_DB = DB_Sitio_Tarjetas
IMAGE = apache-cgi
URL = http://localhost/

APP_DIR = app

SRC_DIR = $(APP_DIR)/src
CGI_DIR = $(APP_DIR)/cgi
INCLUDE_DIR = $(APP_DIR)/include
INCLUDE_DIRS = $(INCLUDE_DIR) $(INCLUDE_DIR)/Application/ $(INCLUDE_DIR)/Domain $(INCLUDE_DIR)/Infrastructure $(INCLUDE_DIR)/Presentation \
	$(INCLUDE_DIR)/Application/Dtos $(INCLUDE_DIR)/Application/Services $(INCLUDE_DIR)/Application/Email $(INCLUDE_DIR)/Application/Email/Interfaces $(INCLUDE_DIR)/Application/Email/Services \
	$(INCLUDE_DIR)/Domain/Models \
	$(INCLUDE_DIR)/Infrastructure/Repositories \
	$(INCLUDE_DIR)/Presentation/Views $(INCLUDE_DIR)/Presentation/Views/Static $(INCLUDE_DIR)/Presentation/Views/Dynamic \
	$(INCLUDE_DIR)/Utils 
CXXFLAGS = -Wall -std=c++17 -pipe $(patsubst %,-I%,$(INCLUDE_DIRS))
DEPFLAGS = -MMD -MP
JOBS ?= 4
MAKEFLAGS += -j$(JOBS)

BUILD_DIR = $(APP_DIR)/build
BIN_DIR = $(APP_DIR)/bin

# =========================

# FUENTES

# =========================

CGI_FILES = $(wildcard $(CGI_DIR)/*.cpp)

SRC_SUBDIRS = Application Domain Infrastructure Presentation \
	Application/Dtos Application/Services Application/Email Application/Email/Interfaces Application/Email/Services \
	Domain/Models \
	Infrastructure/Repositories  \
	Presentation/Views Presentation/Views/Dynamic Presentation/Views/Static \
	Utils
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(foreach d,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)/$(d)/*.cpp))
SRC_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

CGI_OBJECTS = $(patsubst $(CGI_DIR)/%.cpp,$(BUILD_DIR)/cgi_%.o,$(CGI_FILES))
CGI_TARGETS = $(patsubst $(CGI_DIR)/%.cpp,$(BIN_DIR)/%.cgi,$(CGI_FILES))

LDLIBS = -lmariadb -lcrypto

# =========================

# BUILD CGI

# =========================

all: $(CGI_TARGETS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	docker exec $(CONTAINER) sh -c 'mkdir -p "$(dir $@)"'
	docker exec $(CONTAINER) g++ $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

$(BUILD_DIR)/cgi_%.o: $(CGI_DIR)/%.cpp
	docker exec $(CONTAINER) sh -c 'mkdir -p "$(dir $@)"'
	docker exec $(CONTAINER) g++ $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

$(BIN_DIR)/%.cgi: $(BUILD_DIR)/cgi_%.o $(SRC_OBJECTS)
	docker exec $(CONTAINER) mkdir -p app/bin
	docker exec $(CONTAINER) g++ app/build/cgi_$*.o $(SRC_OBJECTS) $(LDLIBS) -o app/bin/$*.cgi
	docker exec $(CONTAINER) chmod +x app/bin/$*.cgi

-include $(SRC_OBJECTS:.o=.d)

@$(MAKE) url

# =========================

# DOCKER

# =========================

image:
	docker build -t $(IMAGE) .

up:
	@docker start $(CONTAINER) 2>/dev/null || docker run -d \
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

db-create:
	@docker run -d \
		--name $(CONTAINER_DB) \
		-p 3306:3306 \
		-e MARIADB_ROOT_PASSWORD=seg_estruct_123456 \
  	-e MARIADB_DATABASE=SITIO_TARJETAS \
  	-e MARIADB_USER=admin \
  	-e MARIADB_PASSWORD=admin_123456 \
  	mariadb

db-up:
	@docker start $(CONTAINER_DB)

db-stop:
	docker stop $(CONTAINER_DB)

db-restart:
	docker restart $(CONTAINER_DB)

db-rm-cont:
	docker rm -f $(CONTAINER_DB)
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

dev: image remove-container up all url

url:
	@echo Servidor iniciado:
	@echo.
	@echo    $(URL)
	@echo.