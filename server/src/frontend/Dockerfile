FROM node:alpine as build
WORKDIR /app

COPY src/frontend/package*.json ./
RUN npm install --legacy-peer-deps

COPY src/frontend/ ./
RUN npm run build


FROM nginx:stable-alpine

COPY src/frontend/nginx.conf /etc/nginx/conf.d/default.conf

COPY --from=build /app/dist /usr/share/nginx/html

EXPOSE 5173

CMD ["nginx", "-g", "daemon off;"]