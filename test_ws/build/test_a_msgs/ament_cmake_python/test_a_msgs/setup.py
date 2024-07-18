from setuptools import find_packages
from setuptools import setup

setup(
    name='test_a_msgs',
    version='0.0.1',
    packages=find_packages(
        include=('test_a_msgs', 'test_a_msgs.*')),
)
