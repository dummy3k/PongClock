import logging.config
import numpy as np

def normalized(a, axis=-1, order=2):
    """
        >>> normalized([1, 0])
        array([[ 1.,  0.]])
        
        >>> normalized([5, 0])
        array([[ 1.,  0.]])
    """
    l2 = np.atleast_1d(np.linalg.norm(a, order, axis))
    l2[l2==0] = 1
    return a / np.expand_dims(l2, axis)
    
def logging_config(): 
    logging.config.dictConfig({ 
        'version': 1,
        'disable_existing_loggers': False,
        'formatters': { 
            'standard': { 
                    'format': '%(asctime)s [%(levelname)-7s] %(name)s: %(message)s',
                    'datefmt': '%Y-%m-%d %H:%M',
            },
            'colored': {
                '()': 'colorlog.ColoredFormatter',
                'format': "%(log_color)s%(levelname)-8s%(reset)s%(name)s %(message)s"
            }		
        },
        'handlers': { 
            'default': { 
                'level': 'DEBUG',
                'formatter': 'colored',
                'class': 'logging.StreamHandler',
            },
        },
        'loggers': { 
            '': { 
                'handlers': ['default'],
                'level': 'WARN',
                'propagate': True
            },
            '__main__': { 
                'handlers': ['default'],
                'level': 'DEBUG',
                'propagate': False
            },
        } 
    })