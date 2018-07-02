pipeline {
    agent none
    stages {
        stage ('Clean') {
            //failFast true
            parallel {
                stage("linux-clean") {
                    agent {
                        label "linux"
                    }
                    steps {
                        dir("build") {
                            deleteDir()
                        }
                        sh 'hostname'
                    }
                }
                stage("win-clean") {
                    agent {
                        label "windows"
                    }
                    steps {
                        dir("build") {
                            deleteDir()
                        }
                        bat 'hostname'
                    }
                }
                stage ( "mac-clean" ){
                    agent {
                        label "mac"
                    }
                    steps {
                        dir("build") {
                            deleteDir()
                        }
                        sh 'hostname'
                    }
                }
            }
        }
        stage ('Build') {
            //failFast true
            parallel {
                stage("linux-build") {
                    agent {
                        label "linux"
                    }
                    steps {
                        checkout scm
                        dir("build") {
                            sh 'cmake .. -DCMAKE_BUILD_TYPE=Release'
                            sh 'make'
                        }
                    }
                }
                stage("win-build") {
                    agent {
                        label "windows"
                    }
                    steps {
                        dir("build") {
                                bat 'cmake .. -G "Visual Studio 15 2017 Win64" '
                                bat "cmake --build . --target Release --config ALL_BUILD"
                            }
                    }
                }
                stage ( "mac-build" ){
                    agent {
                        label "mac"
                    }
                    steps {
                        checkout scm
                        dir("build") {
                            sh 'cmake .. -DCMAKE_BUILD_TYPE=Release'
                            sh 'make'
                        }
                    }
                }
            }
        }

    //     stage ('Test') {
    //         steps {
    //             parallel (
    //                 "linux" : {
    //                     node ("linux") {
    //                         dir('Build') {
    //                             sh 'ctest'
    //                             // Add other test executables here.
    //                         }

    //                     }
    //                 },
    //                 "windows" : {
    //                     node('windows') {
    //                         dir("build") {
    //                             bat 'ctest'
    //                             // Add other test executables here.
    //                         }


    //                     }
    //                 },
    //                 "mac" : {
    //                     node('mac') {
    //                         dir("build") {
    //                             sh 'ctest'
    //                             // Add other test executables here.
    //                         }

    //                     }
    //                 }
    //             )
    //         }
    //     }
    }

}
