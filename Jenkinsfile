pipeline {
    agent {
				label 'idc-dk-i14545.microchip.com'
    }

    parameters {
        string( name: 'NOTIFICATION_EMAIL',
                defaultValue:  'PICAVR_Examples_GateKeepers@microchip.com',
                description: "Email to send build failure, fixed and successful deployment notifications.")
    }
	
	environment {		
		GITHUB_URL ='https://github.com/microchip-pic-avr-examples/atmega328p-discrete-pid-controller-studio.git'
		BITBUCKET_URL = 'https://bitbucket.microchip.com/scm/ebe/atmega328p-discrete-pid-controller-studio.git'
		DEPLOY_TOOL_URL = 'https://bitbucket.microchip.com/scm/citd/tool-github-deploy.git'
		DEPLOY_SCRIPT_DIR = 'tool-github-deploy'
		DEPLOY_SCRIPT_FILE = 'deploy-source-as-is.sh'
	}

    options {
        timestamps()
        timeout(time: 20, unit: 'MINUTES')
    }

    stages {
        stage('Checkout') {
            steps {
				checkout scm
            }
        }

		stage('Build') {
            steps {
				script {
					execute("git clone https://bitbucket.microchip.com/scm/~i20936/tool-studio-c-build.git")
					execute("cd tool-studio-c-build && python studiobuildtool.py")	
							
				}
            }
        }	
		
        stage('Deploy') {
			when {
				not { 
					changeRequest() 
				}
				anyOf {
					tag ''
				}
            }
			steps {
				script {
					execute("git clone ${env.DEPLOY_TOOL_URL}")		
					
					withCredentials([usernamePassword(credentialsId: '8bit-examples.github.com', usernameVariable: 'USER_NAME', passwordVariable:'USER_PASS' )]) {					
						execute("cd ${env.DEPLOY_SCRIPT_DIR} && sh ${env.DEPLOY_SCRIPT_FILE} ${env.BITBUCKET_URL} ${env.GITHUB_URL} ${USER_NAME} ${USER_PASS} '--tag ${env.TAG_NAME}'")
					}	

                    sendSuccessfulGithubDeploymentEmail()					
				}
			}
        }		
	}

    post {
        failure {			
            script {			
				sendPipelineFailureEmail()
            }
        }
        always {
            archiveArtifacts artifacts: "tool-studio-c-build/output/**", allowEmptyArchive: true, fingerprint: true
			script{
				cleanWs()
			}
        }
    }
}

def execute(String cmd) {
	if(isUnix()) {
		sh cmd
	} else {
		bat cmd
	}
}

def sendPipelineFailureEmail () {
    if (!"${env.CHANGE_AUTHOR_EMAIL}".equalsIgnoreCase("null")) {		  
        mail to: "${env.CHANGE_AUTHOR_EMAIL}, ${params.NOTIFICATION_EMAIL}",
        subject: "Failed Pipeline: ${currentBuild.fullDisplayName}",
        body: "Pipeline failure. ${env.BUILD_URL}"
    } else {			  
        mail to: "${params.NOTIFICATION_EMAIL}",
        subject: "Failed Pipeline: ${currentBuild.fullDisplayName}",
        body: "Pipeline failure. ${env.BUILD_URL}"
    }
}

def sendSuccessfulGithubDeploymentEmail () {
    mail to: "${params.NOTIFICATION_EMAIL}",
    subject: "Successful Deployment: ${currentBuild.fullDisplayName}",
    body: "The changes have been successfully deployed to GitHub. ${env.GITHUB_URL}"
}