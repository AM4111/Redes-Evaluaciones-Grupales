FROM gcc:4.9

WORKDIR /app

COPY app/. .

RUN gcc -o myapp t2.c -lm

CMD ["./myapp"]