FROM node:17-alpine as build
WORKDIR /app

# Install dependencies
COPY package.json yarn.lock ./
RUN yarn install

# Build app
COPY ./ ./
RUN yarn build

# Copy to nginx to serve static files
FROM nginx
COPY --from=build /app/build /usr/share/nginx/html
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
