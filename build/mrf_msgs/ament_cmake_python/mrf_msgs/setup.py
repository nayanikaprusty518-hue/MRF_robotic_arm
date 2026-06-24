from setuptools import find_packages
from setuptools import setup

setup(
    name='mrf_msgs',
    version='0.1.0',
    packages=find_packages(
        include=('mrf_msgs', 'mrf_msgs.*')),
)
