Build the example:

docker build --no-cache --tag NemuHelloWorldAlpineImage .

Run the example:

docker run -p 8000:80 NemuHelloWorldAlpineImage

Connect from browser on 127.0.0.1:8000