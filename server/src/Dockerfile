FROM gcc:16-trixie as build

WORKDIR /app

RUN apk --update add --no-cache \
  && rm -rf /var/cache/apk/*

ADD server/include /app/include
ADD ../include/cxxchecker_reflection.hpp /app/include/cxxchecker_reflection.hpp

RUN g++ -std=c++26 -x c++-header -c include/standard_libs.hpp -o include/standard_libs.hpp.gch -O2
RUN g++ -std=c++26 -x c++-header -c include/cxxchecker_reflection.hpp -o include/cxxchecker_reflection.hpp.gch -O2

COPY src/TaskEvaluator.cpp /app/
RUN g++ -std=c++26 -freflection TaskEvaluator.cpp -o TaskEvaluator -O2

COPY src/RestApi.cpp /app/
RUN g++ -std=c++26 -freflection RestApi.cpp -o RestApi -pthread -O2

RUN rm -rf /var/cache/apk/*



FROM alpine:latest

WORKDIR /app

RUN apk --update add --no-cache \
  g++ \
  curl \
  bubblewrap \
  make

COPY --from=build /app/include/standard_libs.hpp /app/include/
COPY --from=build /app/include/standard_libs.hpp.gch /app/include/
COPY --from=build /app/include/cxxchecker_reflection.hpp /app/include/
COPY --from=build /app/include/cxxchecker_reflection.hpp.gch /app/include/

COPY --from=build /app/TaskEvaluator /app/
COPY --from=build /app/RestApi /app/

ADD /tasks /app/tasks

RUN mkdir /app/temp/

CMD [ ".RestApi" ]