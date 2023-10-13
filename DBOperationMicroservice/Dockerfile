FROM golang:1.19

WORKDIR /home/kai/projects/DBOperationMicroservice

ENV GIN_MODE=release
ENV PORT=8000

COPY . .

RUN go build -o main .

EXPOSE $PORT

CMD ["./main"]
