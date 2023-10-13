package repositories

import (
	"fmt"
	"log"
	"os"

	"DBOperationMicroservice/models"

	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/postgres"
	"github.com/joho/godotenv"
)

var DB *gorm.DB

func InitDB() (*gorm.DB, error) {
	if err := godotenv.Load(); err != nil {
		log.Fatalf("Error loading .env file: %v", err)
	}

	dbHost := os.Getenv("DB_HOST")
	dbPort := os.Getenv("DB_PORT")
	dbUser := os.Getenv("DB_USER")
	dbPassword := os.Getenv("DB_PASSWORD")
	dbName := os.Getenv("DB_NAME")

	connectionString := fmt.Sprintf("postgres://%s:%s@%s:%s/%s", dbUser, dbPassword, dbHost, dbPort, dbName)

	db, err := gorm.Open("postgres", connectionString)

	if err != nil {
		fmt.Println("Error opening database")
		return nil, err
	}

	db.LogMode(true)
	db.AutoMigrate(&models.Order{})

	DB = db

	return db, nil

}

func CloseDB() {
	if DB != nil {
		DB.Close()
	}
}

func CreateOrder(order *models.Order) error {
	return DB.Create(order).Error
}

func GetOrderByOrderID(id string) (*models.Order, error) {
	var order models.Order
	if err := DB.Where("order_id = ?", id).First(&order).Error; err != nil {
		return nil, err
	}
	return &order, nil
}
