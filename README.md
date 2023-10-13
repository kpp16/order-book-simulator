# Stock Market Order Book Simulator

## Overview

This project is a comprehensive stock market order book simulator and microservice system designed to mimic stock market trading operations. It combines a C++ program for simulating stock orders with a Go-based microservice that handles asynchronous data processing and database operations. The system is containerized with Docker and deployable in a Kubernetes cluster for scalability and high availability.


## Key Features

- **Stock Market Simulation**: The C++ program allows users to connect via sockets and submit stock orders in JSON format, which are processed in a simulated order book.

- **Go Microservice**: The Go-based microservice handles asynchronous CRUD operations for orders, logs data to a PostgreSQL database, and communicates with the C++ program via asynchronous HTTP operations.

- **Docker Containerization**: Both the C++ program and the Go microservice are containerized using Docker, making them easily deployable across various environments.

- **PostgreSQL Database**: Order data is stored in a PostgreSQL database, providing data persistence and retrieval capabilities.

- **GitHub Container Registry**: The Docker image of the Go microservice is hosted on the GitHub Container Registry for easy distribution.

- **Kubernetes Cluster**: The system is designed to be deployed in a Kubernetes cluster, where it can be scaled horizontally for load balancing and high availability.

- **Kubernetes Service**: A Kubernetes service acts as a single entry point to the cluster, enabling load balancing and efficient routing of incoming traffic.

## Prerequisites

To run this project, you will need:

- Clang: For compiling the C++ program with C++20 features.
- CMake: To build the C++ program.
- Go 1.19: To build and run the Go microservice.
- Docker: To build and run the containerized applications.
- Kubernetes: To deploy the system in a Kubernetes cluster.
- PostgreSQL: To set up the database for order data storage.
- nlohmann-json3-dev: For handling JSON data in the C++ program.

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/your-username/stock-market-simulator.git
cd stock-market-simulator
```

### Build and Run the Docker Container for the Go Microservice
1. Naviagte to the Go microservice
```bash
cd DBOperationMicroservice/
```

2. Build the Docker image for the Go microservice, specifying your desired image name (e.g., dbo-microservice):
```bash
docker build -t dbo-microservice .
```

3. You can host the docker image in docker desktop, ghcr, etc. Change the path in `orderbook-sim/DBOperationMicroservice/deployment.yaml` to reflect accordingly.

### Deploy in a Kubernetes Cluster

1.Deploy the system in a Kubernetes cluster by applying the YAML configuration files.
```bash
kubectl apply -f deployment.yaml
kubectl apply -f service.yaml
```

After applying the configurations, you can change `CLUSTER_URL` variable in the `Dockerfile` in `orderbook-sim/C++app` to the external URL of the cluster.

### Build and Run the Docker Container for the C++ Program

1. Navigate to the C++ program directory
```bash
cd C++app
```

2. Build the Docker image for the C++ program, specifying your desired image name (e.g., order-book):

```bash
docker build -t order-book.
```

3. Run the Docker container for the Go microservice, mapping a host port to the container's exposed port (port 8081 on the host to port 80 in the container) to allow access:

```bash
docker run -p 8080:8080 order-book
```

4. Use a tool like `netcat` to connect to the socket application running in the docker container:
```bash
nc localhost 8080
```

### Order JSON format
```JSON
{
    "type": "order",
    "ticker": "<string>",
    "price": <double>,
    "quantity": <double>,
    "action": "buy/sell"
}
```

### Example order:
```JSON
{
    "type": "order",
    "ticker": "AAPL",
    "price": 178.85,
    "quantity": 130,
    "action":  "buy"
}

```

## Acknowledgments
Special thanks to the open-source communities of Clang, CMake, C++20, Go, Gin, PostgreSQL, Docker, and Kubernetes for the tools and technologies that make this project possible.