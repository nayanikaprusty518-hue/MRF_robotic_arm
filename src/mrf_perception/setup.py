from setuptools import setup

package_name = 'mrf_perception'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='sairajesh',
    maintainer_email='sairajesh@avartanlabs.com',
    description='Simulated perception layer publishing the detector-agnostic object interface.',
    license='MIT',
    entry_points={
        'console_scripts': [
            'perception = mrf_perception.perception:main',
        ],
    },
)
