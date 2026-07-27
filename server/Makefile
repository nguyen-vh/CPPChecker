.PHONY: build sbuild up down re logs cd

default: sbuild

build:
	docker compose build

sbuild:
	docker compose up --build

up:
	docker compose up -d

down:
	docker compose down

re:	down build up

logs:
	docker compose logs

cd:
	docker compose exec -it uni_server /bin/sh

help:
	@echo "Available targets: "
	@echo "  make					- Build and start Docker container"
	@echo "  make build		- Build Docker image"
	@echo "  make sbuild	- Build and start Docker container"
	@echo "  make up			- Start Docker container"
	@echo "  make down		- Stop and remove Docker container"
	@echo "  make re			- make down + make build + make up"
	@echo "  make logs		- Show Docker container logs"
	@echo "  make cd			- Change directory to Docker container directory. Use > exit < to get out"
	@echo "  make help		- Display this help message"