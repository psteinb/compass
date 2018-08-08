pipeline {
  agent {
    node {
      label 'linux'
    }

  }
  stages {
    stage('error') {
      steps {
        sh '''#!/bin/bash
date'''
      }
    }
  }
}