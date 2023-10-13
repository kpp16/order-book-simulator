package main

import (
	"DBOperationMicroservice/repositories"
	"DBOperationMicroservice/routes"

	"github.com/gin-gonic/gin"
	_ "github.com/lib/pq"
)

func main() {
	_, err := repositories.InitDB()
	if err != nil {
		panic("Failed to connect to the database")
	}
	defer repositories.CloseDB()

	r := gin.Default()

	routes.InitRoutes(r)

	r.Run(":8080")
}
