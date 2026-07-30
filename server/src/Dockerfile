FROM gcc:16-trixie as build

WORKDIR /app

RUN apt-get update && apt-get install -y \
  --no-install-recommends \
  libboost-all-dev \
  && rm -rf /var/lib/apt/lists/*

ADD include /app/include

RUN g++ -std=c++26 -freflection -x c++-header -c include/standard_libs.hpp -o include/standard_libs.hpp.gch -O2
RUN g++ -std=c++26 -freflection -x c++-header -c include/cxxchecker_reflection.hpp -o include/cxxchecker_reflection.hpp.gch -O2

COPY src/TaskEvaluator.cpp /app/
RUN g++ -std=c++26 -freflection TaskEvaluator.cpp -o TaskEvaluator -O2

COPY src/RestApi.cpp /app/
RUN g++ -std=c++26 RestApi.cpp -o RestApi -pthread -O2

RUN rm -rf /var/cache/apk/*



FROM gcc:16-trixie

WORKDIR /app

RUN apt-get update && apt-get install -y \
  --no-install-recommends \
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

CMD [ "./RestApi" ]