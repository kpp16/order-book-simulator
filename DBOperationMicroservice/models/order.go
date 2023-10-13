package models

import (
	"github.com/jinzhu/gorm"
)

type Order struct {
	gorm.Model
	Order_id string  `json:"id"`
	Price    float64 `json:"price"`
	Quantity float64 `json:"quantity"`
	Time     int64   `json:"time"`
	Ticker   string  `json:"ticker"`
	Status   string  `json:"status"`
}
