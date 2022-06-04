# -*- coding: utf-8 -*-
from setuptools import setup, find_packages
import os

setup(
    name="lumixlapse",
    author="Adam Haile",
    author_email="adammhaile@gmail.com",
    version='1.0.0',
    description="Trigger lumix camera from execonmcode",
    long_description='',
    url="https://github.com/adammhaile/Rancor",
    license="GNU Affero General Public License v3 or later (AGPLv3+)",
    packages=find_packages(exclude=[]),
    include_package_data=True,
    entry_points={
            'console_scripts': [
                'lumixlapse = lumix:main'
            ]
        },
    install_requires=['requests'],
    dependency_links=[],
    classifiers=[
        "Development Status :: 4 - Beta",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Environment :: Console",
        "Natural Language :: English",
    ]
)