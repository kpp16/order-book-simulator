package handlers

import (
	"fmt"
	"net/http"

	"DBOperationMicroservice/models"
	"DBOperationMicroservice/repositories"

	"github.com/gin-gonic/gin"
)

func HelloHandler(c *gin.Context) {
	c.String(http.StatusOK, "Hello, World!")
}

func EchoHandler(c *gin.Context) {
	var jsonMap map[string]interface{}

	if err := c.ShouldBindJSON(&jsonMap); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	fmt.Println("Received JSON: ", jsonMap)

	c.JSON(http.StatusOK, gin.H{"message": "JSON data received successfully"})
}

func AddOrder(c *gin.Context) {
	var jsonMap map[string]interface{}

	if err := c.ShouldBindJSON(&jsonMap); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	fmt.Println("Received JSON: ", jsonMap)

	order_id := jsonMap["id"]
	price := jsonMap["price"]
	quantity := jsonMap["quantity"]
	time := jsonMap["time"]
	ticker := jsonMap["ticker"]
	status := jsonMap["status"]

	if order_id == nil || price == nil || quantity == nil || time == nil || ticker == nil || status == nil {
		c.JSON(http.StatusBadRequest, gin.H{"message": "Error creating order"})
		return
	}

	order := models.Order{
		Order_id: order_id.(string),
		Price:    price.(float64),
		Quantity: quantity.(float64),
		Time:     int64(time.(float64)),
		Ticker:   ticker.(string),
		Status:   status.(string),
	}

	go func() {
		err := repositories.CreateOrder(&order)
		if err == nil {
			c.JSON(http.StatusOK, gin.H{"message": "Order added successfully"})
		} else {
			c.JSON(http.StatusBadRequest, gin.H{"message": "Error creating order"})
		}
		return
	}()

	c.JSON(http.StatusOK, gin.H{
		"message": "Async order creation started",
	})

}

func GetOrder(c *gin.Context) {
	order_id := c.Query("id")

	fmt.Println("Get ordered called")

	if order_id == "" {
		c.JSON(http.StatusBadRequest, gin.H{"message": "Error fetching order"})
		return
	}

	order, err := repositories.GetOrderByOrderID(order_id)

	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"message": "Error fetching order"})
		return
	}

	c.JSON(http.StatusOK, gin.H{"order": order})
}
