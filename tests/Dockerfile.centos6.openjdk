
# Build from top directory with:
#   docker build -t test/cld:centos6-openjdk -f tests/Dockerfile.centos6.openjdk .
FROM  centos:6

RUN   yum install -y java-1.8.0-openjdk java-1.8.0-openjdk-devel \
                     wget \
                     gcc gcc++ *gcc-c++*
RUN   yum groupinstall -y 'Development Tools'

ENV    M2_HOME /usr/local/apache-maven/apache-maven-3.2.1
ENV    M2      $M2_HOME/bin
ENV    PATH    $M2:$PATH

# Install Maven2
RUN   mkdir /usr/local/apache-maven && \
      cd /usr/local/apache-maven && \
      wget http://mirror.olnevhost.net/pub/apache/maven/binaries/apache-maven-3.2.1-bin.tar.gz && \
      tar xvf apache-maven-3.2.1-bin.tar.gz && \
      rm apache-maven-3.2.1-bin.tar.gz

ENV    AUTOCONF_VERSION 2.69
RUN    cd /tmp && \
       wget http://ftp.gnu.org/gnu/autoconf/autoconf-${AUTOCONF_VERSION}.tar.gz && \
       tar xvzf autoconf-${AUTOCONF_VERSION}.tar.gz && \
       cd autoconf-${AUTOCONF_VERSION} && \
       ./configure && \
       make && \
       make install && \
       rm -rf autoconf-${AUTOCONF_VERSION}.tar.gz autoconf-${AUTOCONF_VERSION}

ENV    AUTOMAKE_VERSION 1.15
RUN    cd /tmp && \
       wget http://ftp.gnu.org/gnu/automake/automake-${AUTOMAKE_VERSION}.tar.gz && \
       tar xvzf automake-${AUTOMAKE_VERSION}.tar.gz && \
       cd automake-${AUTOMAKE_VERSION} && \
       ./configure && \
       make && \
       make install && \
       rm -rf automake-${AUTOMAKE_VERSION}.tar.gz automake-${AUTOMAKE_VERSION}

ENV    LIBTOOL_VERSION 2.4
RUN    cd /tmp && \
       wget http://ftp.gnu.org/gnu/libtool/libtool-${LIBTOOL_VERSION}.tar.gz && \
       tar xvzf libtool-${LIBTOOL_VERSION}.tar.gz && \
       cd libtool-${LIBTOOL_VERSION} && \
       ./configure && \
       make && \
       make install && \
       rm -rf libtool-${LIBTOOL_VERSION}.tar.gz libtool-${LIBTOOL_VERSION}

COPY     . /opt/cld
WORKDIR  /opt/cld

# C++ compile, test and install
RUN      cd /opt/cld && \
         aclocal && \
         libtoolize --force && \
         automake --add-missing && \
         autoreconf && \
         ./configure && \
         make clean && \
         make && \
         make check && \
         make install

RUN      echo "/usr/local/lib/cld" >> /etc/ld.so.conf.d/cld.conf && \
         ldconfig

# Java build and test
RUN      cd /opt/cld/ports/java && \
         mvn test
