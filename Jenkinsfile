pipeline {
    agent { label 'swarm' }
    post {
      failure {
        updateGitlabCommitStatus name: 'build', state: 'failed'
        slackSend color: 'danger', message: "FAILED: ${env.JOB_NAME} #${env.BUILD_NUMBER} - ${BUILD_URL}"
      }
      success {
        updateGitlabCommitStatus name: 'build', state: 'success'
      }
      always { 
        junit allowEmptyResults: true, testResults: '**/target/surefire-reports/*.xml'
      }
    }
    options {
      gitLabConnection('git.ozan.com')
      gitlabBuilds(builds: ['build'])
      buildDiscarder(logRotator(numToKeepStr: '10'))
    }
    triggers {
      gitlab(triggerOnPush: true, triggerOnMergeRequest: true, branchFilterType: 'All')
    }
    tools {
      maven 'maven'
    }
    stages {
      stage('build'){
        steps{
          sh 'mvn clean install -Dmaven.javadoc.skip=true -U -B -DskipTests -DskipITs -Djetty.skip=true'
        }
      }
      stage('deploy') {
        when {
          branch 'feature/eft-changes'
        }
        steps {
          configFileProvider([configFile(fileId: 'maven-settings', targetLocation: 'maven-settings', variable: 'MAVEN_SETTINGS')]) {
            sh 'mvn -B -s $MAVEN_SETTINGS -Dmaven.javadoc.skip=true deploy -U -DskipTests -DskipITs -Djetty.skip=true'
          }
        }
      }
    }
}