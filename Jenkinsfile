pipeline {
    //agent { label "linux" }
    agent any
    stages {
        stage ('Clean') {
            steps {
                parallel (
                    "linux" : {
                        node ("linux") {
                            dir("build") {
                                deleteDir()
                            }
                            sh 'hostname'
                        }
                    },
                    "windows" : {
                        node('windows') {
                            dir("build") {
                                deleteDir()
                            }
                            bat 'hostname'
                        }
                    },
                    "mac" : {
                        node('mac') {
                            dir("build") {
                                deleteDir()
                            }
                            sh 'hostname'
                        }
                    }
                )
            }
        }

        stage ('Build') {
            steps {
                parallel (
                    "linux" : {
                        node ("linux") {
                            checkout scm
                            dir("build") {
                                sh 'cmake .. -DCMAKE_BUILD_TYPE=Release'
                                sh 'make'
                            }
                        }
                    },
                    "windows" : {
                        node('windows') {
                            checkout(changelog: false, scm: scm) // Changelog to false, otherwise Jenkins shows duplicates. Only linux (the Jenkins master) has the changelog enabled.
                            dir("build") {
                                bat 'cmake .. -G "Visual Studio 15 2017 Win64" '
                                bat "cmake --build . --target Release --config ALL_BUILD"
                            }
                        }
                    },
                    "mac" : {

                        try
                        {
                            timeout(time: 60, unit: 'SECONDS') {
                                node('mac') {
                                    checkout(changelog: false, scm: scm) // Changelog to false, otherwise Jenkins shows duplicates. Only linux (the Jenkins master) has the changelog enabled.
                                    dir("build") {
                                        sh 'cmake .. -DCMAKE_BUILD_TYPE=Release'
                                        sh 'make'
                                    }
                                }
                            }
                        } catch(err) {
                            // Uh-oh. welles not available, so use 'cage'.
                            echo 'Time out on mac. Node down?'
                        }
                    }
                )
            }
        }

        stage ('Test') {
            steps {
                parallel (
                    "linux" : {
                        node ("linux") {
                            dir('Build') {
                                sh 'ctest'
                                // Add other test executables here.
                            }

                        }
                    },
                    "windows" : {
                        node('windows') {
                            dir("build") {
                                bat 'ctest'
                                // Add other test executables here.
                            }


                        }
                    },
                    "mac" : {
                        node('mac') {
                            dir("build") {
                                sh 'ctest'
                                // Add other test executables here.
                            }

                        }
                    }
                )
            }
        }
    }

}
