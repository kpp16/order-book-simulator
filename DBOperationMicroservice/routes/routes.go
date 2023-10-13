package routes

import (
	"DBOperationMicroservice/handlers"

	"github.com/gin-gonic/gin"
)

func InitRoutes(r *gin.Engine) {
	// Define routes here.
	r.GET("/", handlers.HelloHandler)
	r.GET("/getorder", handlers.GetOrder)

	r.POST("/echo", handlers.EchoHandler)
	r.POST("/addorder", handlers.AddOrder)
}
